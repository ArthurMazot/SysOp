#pragma once
#include <unistd.h>
#include "cpu.hpp"
#include "hwso.hpp"
#include "programas.hpp"
#include "memory.hpp"
#include "enum.hpp"

CPU::CPU(Memory *_mem, int tamP){
    maxInt = 32767;
    minInt = -32767;
    mem = _mem;
    tamPag = tamP;}

CPU::~CPU(){}

int CPU::logicoFisico(int e, PCB *p){
    return p->tabPagS[(e/tamPag)]*tamPag + e%tamPag;}

void CPU::savePCB(PCB *p){
    p->pc = pc;
    for(int i = 0; i < 10; i++)
        p->regs[i] = reg[i];}

void CPU::loadPCB(PCB *p){
    pc = p->pc;
    for(int i = 0; i < 10; i++)
        reg[i] = p->regs[i];}

bool CPU::legal(int e, PCB *p){
    if(e >= 0 && e < tamPag*(p->tabPagP[0]-1) + (p->offset ? p->offset : tamPag))
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

Interrupts CPU::run(PCB *p){
    irpt = noInterrupt;
    int count = 0;
    loadPCB(p);
    while(count++ < 5){
        if(legal(pc, p)){
            if(p->tabPagS[pc/tamPag] == -1){
                p->end = pc;
                savePCB(p);
                p->irpt = pageFault;
                return pageFault;}
            usou[p->tabPagS[pc/tamPag]] = 1;
            ir = mem->pos[logicoFisico(pc, p)];

            switch (ir.opc){
                case LDI:
                    reg[ir.ra] = ir.p;
                    pc++;
                    break;

                case LDD:
                if(legal(ir.p, p)){
                    if(p->tabPagS[ir.p/tamPag] == -1){
                        p->end = ir.p;
                        savePCB(p);
                        p->irpt = pageFault;
                        return pageFault;}
                    reg[ir.ra] = mem->pos[logicoFisico(ir.p, p)].p;
                    pc++;}
                    break;

                case LDX:
                    if(legal(reg[ir.rb], p)){
                        if(p->tabPagS[reg[ir.rb]/tamPag] == -1){
                            p->end = reg[ir.rb];
                            savePCB(p);
                            p->irpt = pageFault;
                            return pageFault;}
                        reg[ir.ra] = mem->pos[logicoFisico(reg[ir.rb], p)].p;
                        pc++;}
                        break;

                case STD:
                    if(legal(ir.p, p)){
                        if(p->tabPagS[ir.p/tamPag] == -1){
                            p->end = ir.p;
                            savePCB(p);
                            p->irpt = pageFault;
                            return pageFault;}
                        int e = logicoFisico(ir.p, p);
                        mem->pos[e].opc = DATA;
                        mem->pos[e].p = reg[ir.ra];
                        pc++;}
                    break;

                case STX:
                    if (legal(reg[ir.ra], p)){
                        if(p->tabPagS[reg[ir.ra]/tamPag] == -1){
                            p->end = reg[ir.ra];
                            savePCB(p);
                            p->irpt = pageFault;
                            return pageFault;}
                        
                        int e = logicoFisico(reg[ir.ra], p);
                        mem->pos[e].opc = DATA;
                        mem->pos[e].ra = -1;
                        mem->pos[e].rb = -1;
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
                        if(p->tabPagS[ir.p/tamPag] == -1){
                            p->end = ir.p;
                            savePCB(p);
                            p->irpt = pageFault;
                            return pageFault;}
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
                        if (reg[ir.rb] > 0){
                            if(p->tabPagS[ir.p/tamPag] == -1){
                                p->end = ir.p;
                                savePCB(p);
                                p->irpt = pageFault;
                                return pageFault;}
                            pc = mem->pos[logicoFisico(ir.p, p)].p;}
                        else pc++;}
                    break;

                case JMPILM:
                    if(legal(ir.p, p)){
                        if(reg[ir.rb] < 0){
                            if(p->tabPagS[ir.p/tamPag] == -1){
                                p->end = ir.p;
                                savePCB(p);
                                p->irpt = pageFault;
                                return pageFault;}
                            pc = mem->pos[logicoFisico(ir.p, p)].p;}
                        else pc++;}
                    break;

                case JMPIEM:
                    if(legal(ir.p, p)){
                        if(reg[ir.rb] == 0){
                            if(p->tabPagS[ir.p/tamPag] == -1){
                                p->end = ir.p;
                                savePCB(p);
                                p->irpt = pageFault;
                                return pageFault;}
                            pc = mem->pos[logicoFisico(ir.p, p)].p;}
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
                    savePCB(p);
                    if(legal(p->regs[9], p))
                        if(p->tabPagS[p->regs[9]/tamPag] == -1){
                            p->end = p->regs[9];
                            p->irpt = pageFault;
                            return pageFault;}
                    
                    p->irpt = IO;
                    pc++;
                    savePCB(p);
                    return IO;

                case STOP:
                    sysCall->stop(p);
                    return Stop;

                default:
                    irpt = intInstrucaoInvalida;
                    break;}} //fim switch e if(legal)

            if(irpt != noInterrupt){
                ih->handle(irpt, p);
                p->irpt = irpt;
                savePCB(p);
                return irpt;} //teve interrupção

            usleep(50000);} //50ms
            savePCB(p);
            p->irpt = irpt;
            return irpt;} //não teve interrupção