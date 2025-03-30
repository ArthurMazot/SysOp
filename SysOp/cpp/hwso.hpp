#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "enum.hpp"

struct CPU;

struct HW{
    public:
    Memory *mem;
    CPU *cpu;
    HW(int);
    ~HW();
};

struct InterruptHandling{
    HW *hw;
    InterruptHandling(HW*);
    ~InterruptHandling();
    void handle(Interrupts);
};

struct SysCallHandling{
    HW *hw;
    SysCallHandling(HW*);
    ~SysCallHandling();
    void stop();
    void handle();
};

struct Utilities{
    HW *hw;
    Utilities(HW *_hw);
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
    SO(HW*);
    ~SO();
};