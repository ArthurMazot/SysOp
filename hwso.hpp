#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "GMGP.hpp"
#include "cpu.hpp"
#include "enum.hpp"
#include "IO.hpp"
struct CPU;

struct HW{
    public:
    Memory *mem;
    CPU *cpu;
    HW(Memory*, int);
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
    Utilities(HW*);
    ~Utilities();
    void loadProgram(Program*);
    void dump(Word&);
    void dump(int, int);
    void loadAndExec(Program*);
};

struct Escalonador{
    vector<PCB*> executando;
    HW *hw;
    GP *gp;
    char trace;

    Escalonador(HW*, Memory*, int, int, char);
    ~Escalonador();
    void addExec(PCB*);
    void rmExec(int);
    void escalonadorRun();
};

struct SO{
    InterruptHandling *ih;
    SysCallHandling *sc;
    Utilities *utils;
    Escalonador *esc;
    SO(HW*, Memory*, int, int);
    ~SO();
};