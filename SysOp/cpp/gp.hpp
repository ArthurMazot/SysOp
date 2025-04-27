#ifndef GP_H
#define GP_H

#include <vector>
#include <iostream>
#include "gm.hpp"
#include "pcb.hpp"
#include "memory.hpp"

class GP{
private:
    int tamPag;
    std::vector<PCB*> processosProntos;
    std::vector<Word>& mem;
    GM gm;

public:
    GP(std::vector<Word>& m, int tamP);
    bool criaProcesso(std::vector<Word>& prog);
    void desalocaProcesso(int id);
    ~GP();
};

#endif