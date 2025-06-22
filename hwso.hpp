#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "GMGP.hpp"
#include "cpu.hpp"
#include "enum.hpp"

struct CPU;

struct HW{
    public:
    CPU *cpu;
    Memory *memP;
    Memory *memS;
    HW(Memory*, Memory*, int);
    ~HW();
};

struct InterruptHandling{
    HW *hw;
    InterruptHandling(HW*);
    ~InterruptHandling();
    void handle(Interrupts, PCB*);
};

struct SysCallHandling{
    HW *hw;
    SysCallHandling(HW*);
    ~SysCallHandling();
    void stop(PCB*);
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
    vector<PCB*> bloqueado;
    HW *hw;
    GP *gp;
    char trace;

    Escalonador(HW*, Memory*, Memory*, int, int, int, char);
    ~Escalonador();
    void addExec(PCB*);
    void rmExec(int);
    void addBloq(PCB*);
    void pageFaultRun();
    void escalonadorRun();
    void IORun();
};

struct SO{
    InterruptHandling *ih;
    SysCallHandling *sc;
    Utilities *utils;
    Escalonador *esc;
    SO(HW*, Memory*, Memory*, int, int, int);
    ~SO();
};