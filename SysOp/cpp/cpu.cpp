#pragma once
#include "cpu.hpp"
#include "hwso.hpp"
#include "programas.hpp"
#include "memory.hpp"
#include "enum.hpp"

CPU::CPU(Memory *_mem, bool _debug){
    maxInt = 32767;
    minInt = -32767;
    mem = _mem;
    debug = _debug;}

CPU::~CPU(){}

void CPU::setAddressOfHandlers(InterruptHandling *_ih, SysCallHandling *_sysCall){
    ih = _ih;
    sysCall = _sysCall;}

void CPU::setUtilities(Utilities *_u){
    u = _u;}

bool CPU::legal(int e){
    if (e >= 0 && e < mem->size)
        return true;
    irpt = intEnderecoInvalido;
    return false;}

bool CPU::testOverflow(int v){
    if ((v < minInt) || (v > maxInt)){
        irpt = intOverflow;
        return false;}
    return true;}

void CPU::setContext(int _pc){
    pc = _pc;
    irpt = noInterrupt;}

void CPU::run(){
	cpuStop = false;
	while(!cpuStop){
		if(legal(pc)){
			ir = mem->pos[pc];
			if(debug){
				cout << "regs: ";
				for (int i = 0; i < 10; i++)
					cout << "r[" << i << "]: " << reg[i];
				cout << endl << "pc: " << pc << endl << "exec: ";
                u->dump(ir);}

            switch (ir.opc){
                case LDI:
                reg[ir.ra] = ir.p;
                pc++;
                break;

                case LDD:
                if(legal(ir.p)){
                    reg[ir.ra] = mem->pos[ir.p].p;
                    pc++;}
                    break;

                case LDX:
                    if(legal(reg[ir.rb])) {
                        reg[ir.ra] = mem->pos[reg[ir.rb]].p;
                        pc++;}
                        break;

                case STD:
                    if(legal(ir.p)){
                        mem->pos[ir.p].opc = DATA;
                        mem->pos[ir.p].p = reg[ir.ra];
                        pc++;
                        if(debug)
                            u->dump(ir.p,ir.p+1);}
                    break;

                case STX:
                    if (legal(reg[ir.ra])){
                        mem->pos[reg[ir.ra]].opc = DATA;
                        mem->pos[reg[ir.ra]].p = reg[ir.rb];
                        pc++;}
                    break;

                case MOVE:
                    reg[ir.ra] = reg[ir.rb];
                    pc++;
                    break;

                case ADD:
                    reg[ir.ra] = reg[ir.ra] + reg[ir.rb];
                    testOverflow(reg[ir.ra]);
                    pc++;
                    break;

                case ADDI:
                    reg[ir.ra] = reg[ir.ra] + ir.p;
                    testOverflow(reg[ir.ra]);
                    pc++;
                    break;

                case SUB:
                    reg[ir.ra] = reg[ir.ra] - reg[ir.rb];
                    testOverflow(reg[ir.ra]);
                    pc++;
                    break;

                case SUBI:
                    reg[ir.ra] = reg[ir.ra] - ir.p;
                    testOverflow(reg[ir.ra]);
                    pc++;
                    break;

                case MULT:
                    reg[ir.ra] = reg[ir.ra] * reg[ir.rb];
                    testOverflow(reg[ir.ra]);
                    pc++;
                    break;

                case JMP:
                    pc = ir.p;
                    break;

                case JMPI:
                    if(legal(ir.p))
                        pc = ir.p;
                    break;

                case JMPIM:
                    if(legal(ir.p))
                        pc = mem->pos[ir.p].p;
                    break;

                case JMPIG:
                    if(reg[ir.rb] > 0) pc = reg[ir.ra];
                    else pc++;				
                    break;

                case JMPIGK:
                    if(reg[ir.rb] > 0) pc = ir.p;
                    else pc++;
                    break;

                case JMPILK:
                    if(reg[ir.rb] < 0) pc = ir.p;
                    else pc++;
                    break;

                case JMPIEK:
                    if(reg[ir.rb] == 0) pc = ir.p;
                    else pc++;
                    break;
                            
                case JMPIL:
                    if(reg[ir.rb] < 0) pc = reg[ir.ra];
                    else pc++;
                    break;

                case JMPIE:
                    if(reg[ir.rb] == 0) pc = reg[ir.ra];
                    else pc++;
                    break;

                case JMPIGM:
                    if(legal(ir.p)){
                        if (reg[ir.rb] > 0) pc = mem->pos[ir.p].p;
                        else pc++;}
                    break;

                case JMPILM:
                    if(legal(ir.p)){
                        if(reg[ir.rb] < 0) pc = mem->pos[ir.p].p;
                        else pc++;}
                    break;

                case JMPIEM:
                    if(legal(ir.p)){
                        if(reg[ir.rb] == 0) pc = mem->pos[ir.p].p;
                        else pc++;}
                    break;

                case JMPIGT:
                    if(reg[ir.ra] > reg[ir.rb]) pc = ir.p;
                    else pc++;
                    break;

                case DATA:
                    irpt = intInstrucaoInvalida;
                    break;

                case SYSCALL:
                    sysCall->handle();
                    pc++;
                    break;

                case STOP:
                    sysCall->stop();
                    cpuStop = true;
                    break;

                default:
                    irpt = intInstrucaoInvalida;
                    break;}} //fim switch e if

        if(irpt != noInterrupt){
            ih->handle(irpt);
            cpuStop = true;}}} //fim if, while e run()
