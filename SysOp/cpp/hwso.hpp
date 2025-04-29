#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "GMGP.hpp"
#include "cpu.hpp"
#include "enum.hpp"

struct CPU;

struct HW{
    public:
    Memory *mem;
    CPU *cpu;
    GP *gp;
    HW(int, int, GP*, Memory*);
    ~HW();
};

struct InterruptHandling{
    HW *hw;
    InterruptHandling(HW*);
    ~InterruptHandling();
    void handle(Interrupts, int);
};

struct SysCallHandling{
    HW *hw;
    SysCallHandling(HW*);
    ~SysCallHandling();
    void stop(int);
    void handle();
};

struct Utilities{
    HW *hw;
    Utilities(HW*);
    ~Utilities();
    void loadProgram(Program*);
    void dump(Word&);
    void dump(int, int);
    void loadAndExec(Program*);
};

struct SO {
    InterruptHandling *ih;
    SysCallHandling *sc;
    Utilities *utils;
    GP *gp;
    SO(HW*, int, int, GP*);
    ~SO();
};