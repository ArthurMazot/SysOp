#pragma once
#include "programas.hpp"
#include "memory.hpp"

enum Interrupts : int{
    noInterrupt, intEnderecoInvalido, intInstrucaoInvalida, intOverflow
};

class CPU{
    int maxInt;
    int minInt;
    int pc;
    Word ir;
    int reg[10];
    Interrupts irpt;
    Memory *mem;
    //InterruptHandling ih;
    //SysCallHandling sysCall;
    bool cpuStop;
    bool debug;
    //Utilities u;

    CPU(Memory*, bool);

    ~CPU();
};