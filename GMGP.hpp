#pragma once
#include <vector>
#include "memory.hpp"
#include "programas.hpp"
using namespace std;

struct GM{
    int tamPag;
    int qntPag;
    char *pags;

    GM(int, int);
    ~GM();
    int *aloca(int);
    void desaloca(int*);
};

struct PCB{
    string nome;
    char exec;
    int offset;
    int id;
    int *tabPag;
    int regs[10];
    int pc;

    PCB(int, int*, string, int);
    ~PCB();
    friend ostream &operator<<(ostream&, PCB&);
};

struct GP{
    int tamPag;
    Memory *mem;
    vector<PCB*> prontos;
    GM *gm;

    GP(Memory*, int, int);
    ~GP();
    char criaProcesso(Program*);
    void desalocaProcesso(int);
};