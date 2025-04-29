#pragma once
#include <unistd.h>
#include "cpu.hpp"
#include "hwso.hpp"
#include "programas.hpp"
#include "memory.hpp"
#include "enum.hpp"

extern char flag;

CPU::CPU(Memory *_mem, bool _debug, int tamP){
    maxInt = 32767;
    minInt = -32767;
    mem = _mem;
    debug = _debug;
    tamPag = tamP;
    tamExec = mem->size/tamPag;
    executando = (PCB**)malloc(mem->size/tamP * sizeof(PCB*));}

CPU::~CPU(){
    delete executando;}

void CPU::addExec(PCB *p){
    for(int i = 0; i < tamExec; i++)
        if(!executando[i]){
            executando[i] = p;
            break;}}
            
void CPU::rmExec(int id){
    for(int i = 0; i < tamExec; i++)
        if(executando[i] && executando[i]->id == id){
            executando[i] = nullptr;
            break;}}

void CPU::savePCB(PCB *p){
    p->pc = pc;
    for(int i = 0; i < 10; i++)
        p->regs[i] = reg[i];}

void CPU::loadPCB(PCB *p){
    pc = p->pc;
    for(int i = 0; i < 10; i++)
        reg[i] = p->regs[i];}

bool CPU::legal(int e, PCB *p){
    for(int i = 0; i <= p->tabPag[0]; i++)
        if(e >= i*tamPag && e < i*tamPag + tamPag)
            return true;
    cout << "e: " << e << endl;
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

void CPU::run(){
    int count = 0, i = -1;
    while(flag){
        if(executando[i] && i >= 0) savePCB(executando[i]);
        while(executando[++i] == nullptr) 
            if(i >= tamExec) i = -1;
            else if(flag == 0) return;
        cout << "Trocando para " << executando[i]->nome << endl;
        loadPCB(executando[i]);
        cpuStop = 0;
        while(!cpuStop){
            if(legal(pc, executando[i])){
                ir = mem->pos[executando[i]->tabPag[(pc/tamPag)+1]*tamPag + pc%tamPag];
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
                    if(legal(ir.p, executando[i])){
                        reg[ir.ra] = mem->pos[ir.p].p;
                        pc++;}
                        break;

                    case LDX:
                        if(legal(reg[ir.rb], executando[i])){
                            reg[ir.ra] = mem->pos[reg[ir.rb]].p;
                            pc++;}
                            break;

                    case STD:
                        if(legal(ir.p, executando[i])){
                            int eM = executando[i]->tabPag[(ir.p/tamPag)+1]*tamPag + ir.p%tamPag;
                            mem->pos[eM].opc = DATA;
                            mem->pos[eM].p = reg[ir.ra];
                            pc++;
                            if(debug)
                                u->dump(eM,eM+1);}
                        break;

                    case STX:
                        if (legal(reg[ir.ra], executando[i])){
                            int eM = executando[i]->tabPag[reg[ir.ra]/tamPag + 1]*tamPag + reg[ir.ra]%tamPag;
                            mem->pos[eM].opc = DATA;
                            mem->pos[eM].p = reg[ir.rb];
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
                        if(legal(ir.p, executando[i]))
                            pc = ir.p;
                        break;

                    case JMPI:
                        if(legal(ir.p, executando[i]))
                            pc = ir.p;
                        break;

                    case JMPIM:
                        if(legal(ir.p, executando[i]))
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
                        if(legal(ir.p, executando[i])){
                            if (reg[ir.rb] > 0) pc = mem->pos[ir.p].p;
                            else pc++;}
                        break;

                    case JMPILM:
                        if(legal(ir.p, executando[i])){
                            if(reg[ir.rb] < 0) pc = mem->pos[ir.p].p;
                            else pc++;}
                        break;

                    case JMPIEM:
                        if(legal(ir.p, executando[i])){
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
                        sysCall->stop(executando[i]->id);
                        rmExec(executando[i]->id);
                        irpt = noInterrupt;
                        cpuStop = 1;
                        break;

                    default:
                        irpt = intInstrucaoInvalida;
                        break;}} //fim switch e if(legal)

            if(irpt != noInterrupt){
                ih->handle(irpt, executando[i]->id);
                rmExec(executando[i]->id);
                irpt = noInterrupt;
                cpuStop = 1;}

            if(++count >= tamPag){
                cpuStop = 1;
                count = 0;}

            usleep(100000);} //100ms, while(!cpuStop)
        }} //while(flag)
