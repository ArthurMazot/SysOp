#pragma once
#include "hwso.hpp"
#include "programas.hpp"
#include "memory.hpp"
#include "enum.hpp"

struct CPU{
    int maxInt;
    int minInt;
    int pc;
    Word ir;
    int reg[10];
    Interrupts irpt;
    Memory *mem;
    InterruptHandling *ih;
    SysCallHandling *sysCall;
    bool cpuStop;
    bool debug;
    Utilities *u;
    PCB **executando;
    int tamExec;
    int tamPag;

    CPU(Memory*, bool, int);
    ~CPU();
    void addExec(PCB*);
    void rmExec(int);
    void savePCB(PCB*);
    void loadPCB(PCB*);
    void setAddressOfHandlers(InterruptHandling*, SysCallHandling*);
    void setUtilities(Utilities*);
    bool legal(int, PCB*);
    bool testOverflow(int);
    void setContext(int);
    void run();
};