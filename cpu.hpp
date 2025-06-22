#pragma once
#include "hwso.hpp"
#include "programas.hpp"
#include "memory.hpp"
#include "enum.hpp"

class InterruptHandling;
class SysCallHandling;
class Utilities;

struct CPU{
    int maxInt;
    int minInt;
    int pc;
    PCB* currentPCB;
    Word ir;
    int reg[10];
    Interrupts irpt;
    Memory *mem;
    InterruptHandling *ih;
    SysCallHandling *sysCall;
    bool debug;
    Utilities *u;
    int tamPag;

    CPU(Memory*, bool, int);
    ~CPU();
    int logicoFisico(int e, PCB *p);
    void savePCB(PCB*);
    void loadPCB(PCB*);
    void setAddressOfHandlers(InterruptHandling*, SysCallHandling*);
    void setUtilities(Utilities*);
    bool legal(int, PCB*);
    bool testOverflow(int);
    void setContext(int);
    int run(PCB*);
};