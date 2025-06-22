#pragma once
#include <vector>
#include "memory.hpp"
#include "programas.hpp"
using namespace std;

struct PCB{
    string nome;
    Interrupts irpt;
    char exec;
    int end;
    int offset;
    int id;
    int *tabPagP;
    int *tabPagS;
    int regs[10];
    int pc;

    PCB(int, int*, int*, string, int);
    ~PCB();
    friend ostream &operator<<(ostream&, PCB&);
};

struct GM{
    PCB **processosMemS;
    int tamPag;
    int qntPagP;
    int qntPagS;
    char *pagsP;
    char *usou;
    int clock;

    GM(int, int, int);
    ~GM();
    int *aloca(int);
    int alocaMemSec(int*);
    void desaloca(int*, int*, int*);
};


struct GP{
    int tamPag;
    int *pagsS;
    Memory *memP;
    Memory *memS;
    vector<PCB*> prontos;
    GM *gm;

    GP(Memory*, Memory*, int, int, int);
    void alocaMemSecundaria(PCB*);
    ~GP();
    char criaProcesso(Program*);
    void desalocaProcesso(int);
};