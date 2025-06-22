#pragma once
#include <unistd.h>
#include "cpu.hpp"
#include "hwso.hpp"
#include "programas.hpp"
#include "memory.hpp"
#include "enum.hpp"

CPU::CPU(Memory *_mem, bool _debug, int tamP){
    maxInt = 32767;
    minInt = -32767;
    mem = _mem;
    debug = _debug;
    tamPag = tamP;}

CPU::~CPU(){}

int CPU::logicoFisico(int e, PCB *p){
    return p->tabPag[(e/tamPag)+1]*tamPag + e%tamPag;}

void CPU::savePCB(PCB *p){
    p->pc = pc;
    for(int i = 0; i < 10; i++)
        p->regs[i] = reg[i];}

void CPU::loadPCB(PCB *p){
    pc = p->pc;
    for(int i = 0; i < 10; i++)
        reg[i] = p->regs[i];}

bool CPU::legal(int e, PCB *p){
    if(e >= 0 && e < tamPag*(p->tabPag[0]-1) + (p->offset ? p->offset : tamPag))
        return true;
    irpt = intEnderecoInvalido;
    return false;}

void CPU::setAddressOfHandlers(InterruptHandling *_ih, SysCallHandling *_sysCall){
    ih = _ih;
    sysCall = _sysCall;}

void CPU::setUtilities(Utilities *_u){
    u = _u;}

bool CPU::testOverflow(int v){
    if ((v < minInt) || (v > maxInt)){
        irpt = intOverflow;
        return false;}
    return true;}

void CPU::setContext(int _pc){
    pc = _pc;
    irpt = noInterrupt;}

int CPU::run(PCB *p){
    int count = 0;
    currentPCB = p;
    loadPCB(p);
    while(count++ < 5){
        if(legal(pc, p)){
            ir = mem->pos[logicoFisico(pc, p)];
            if(debug){
                cout << "regs: ";
                for (int i = 0; i < 10; i++)
                    cout << "r[" << i << "]: " << reg[i];
                cout << endl << "exec: ";
                u->dump(ir);}

            switch (ir.opc){
                case LDI:
                reg[ir.ra] = ir.p;
                pc++;
                break;

                case LDD:
                if(legal(ir.p, p)){
                    reg[ir.ra] = mem->pos[logicoFisico(ir.p, p)].p;
                    pc++;}
                    break;

                case LDX:
                    if(legal(reg[ir.rb], p)){
                        reg[ir.ra] = mem->pos[logicoFisico(reg[ir.rb], p)].p;
                        pc++;}
                        break;

                case STD:
                    if(legal(ir.p, p)){
                        int e = logicoFisico(ir.p, p);
                        mem->pos[e].opc = DATA;
                        mem->pos[e].p = reg[ir.ra];
                        pc++;
                        if(debug)
                            u->dump(e,e+1);}
                    break;

                case STX:
                    if (legal(reg[ir.ra], p)){
                        int e = logicoFisico(reg[ir.ra], p);
                        cout << "Endereço Fisico: " << e << endl;
                        mem->pos[e].opc = DATA;
                        mem->pos[e].p = reg[ir.rb];
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
                    if(legal(ir.p, p))
                        pc = ir.p;
                    break;

                case JMPI:
                    if(legal(ir.p, p))
                        pc = ir.p;
                    break;

                case JMPIM:
                    if(legal(ir.p,p))
                        pc = mem->pos[logicoFisico(ir.p, p)].p;
                    break;

                case JMPIG:
                    if(reg[ir.rb] > 0 && legal(reg[ir.ra], p)) pc = reg[ir.ra];
                    else pc++;				
                    break;

                case JMPIGK:
                    if(reg[ir.rb] > 0 && legal(ir.p, p)) pc = ir.p;
                    else pc++;
                    break;

                case JMPILK:
                    if(reg[ir.rb] < 0 && legal(ir.p, p)) pc = ir.p;
                    else pc++;
                    break;

                case JMPIEK:
                    if(reg[ir.rb] == 0 && legal(ir.p, p)) pc = ir.p;
                    else pc++;
                    break;
                            
                case JMPIL:
                    if(reg[ir.rb] < 0 && legal(reg[ir.ra], p)) pc = reg[ir.ra];
                    else pc++;
                    break;

                case JMPIE:
                    if(reg[ir.rb] == 0 && legal(reg[ir.ra], p)) pc = reg[ir.ra];
                    else pc++;
                    break;

                case JMPIGM:
                    if(legal(ir.p, p)){
                        if (reg[ir.rb] > 0) pc = mem->pos[logicoFisico(ir.p, p)].p;
                        else pc++;}
                    break;

                case JMPILM:
                    if(legal(ir.p, p)){
                        if(reg[ir.rb] < 0) pc = mem->pos[logicoFisico(ir.p, p)].p;
                        else pc++;}
                    break;

                case JMPIEM:
                    if(legal(ir.p, p)){
                        if(reg[ir.rb] == 0) pc = mem->pos[logicoFisico(ir.p, p)].p;
                        else pc++;}
                    break;

                case JMPIGT:
                    if(reg[ir.ra] > reg[ir.rb] && legal(ir.p, p)) pc = ir.p;
                    else pc++;
                    break;

                case DATA:
                    irpt = intInstrucaoInvalida;
                    break;

                case SYSCALL:
                    sysCall->handle();
                     if (reg[8] == 1 || reg[8] == 2) {
                    irpt = IOInterrupt;      
                    savePCB(p);              // salva estado corrente
                    return 1;                // retorna para escalonador trocar de processo
    }
                    pc++;
                    break;

                case STOP:
                    sysCall->stop();
                    irpt = noInterrupt;
                    return 2; //2 pra dizer que foi stop

                default:
                    irpt = intInstrucaoInvalida;
                    break;}} //fim switch e if(legal)

            if(irpt != noInterrupt){
                ih->handle(irpt);
                irpt = noInterrupt;
                return 1;} //teve interrupção

            usleep(100000);} //100ms, while(!cpuStop)
            savePCB(p);
            return 0;} //não teve interrupção