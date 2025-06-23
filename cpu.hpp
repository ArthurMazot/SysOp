#pragma once
#include "hwso.hpp"
#include "programas.hpp"
#include "memory.hpp"
#include "enum.hpp"

struct CPU{
    int maxInt;
    int minInt;
    int pc;
    char *usou;
    Word ir;
    int reg[10];
    Interrupts irpt;
    Memory *mem;
    InterruptHandling *ih;
    SysCallHandling *sysCall;
    Utilities *u;
    int tamPag;

    CPU(Memory*, int);
    ~CPU();
    int logicoFisico(int, PCB*);
    void savePCB(PCB*);
    void loadPCB(PCB*);
    void setAddressOfHandlers(InterruptHandling*, SysCallHandling*);
    void setUtilities(Utilities*);
    bool legal(int, PCB*);
    bool testOverflow(int);
    void setContext(int);
    Interrupts run(PCB*);
};