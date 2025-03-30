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

    CPU(Memory*, bool);
    ~CPU();
    void setAddressOfHandlers(InterruptHandling*, SysCallHandling*);
    void setUtilities(Utilities*);
    bool legal(int);
    bool testOverflow(int);
    void setContext(int);
    void run();
};