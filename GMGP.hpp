#pragma once
#include <vector>
#include "memory.hpp"
#include "programas.hpp"
using namespace std;
enum class ProcessState { NEW, READY, RUNNING, BLOCKED, TERMINATED };
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
    ProcessState state;

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