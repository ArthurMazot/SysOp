#include "gp.hpp"

using namespace std;

GP::GP(vector<Word>& m, int tamP) : tamPag(tamP), processosProntos(m.size() / tamP, nullptr), mem(m), gm(m.size(),tamP){}

bool GP::criaProcesso(vector<Word>& prog){
    vector<int> tabPag;
    if(!gm.aloca(prog.size(), tabPag)){ return false;}

    int numPag = static_cast<int>(tabPag.size());
    for (int p = 0; p < numPag; ++p) {
        for (int j = 0; j < tamPag; ++j){
        mem[tabPag[p] * tamPag + j] = prog[p * tamPag + j];
            
        }
    }

    for (size_t i = 0; i < processosProntos.size(); ++i){
        if(processosProntos[i] == nullptr){
            processosProntos[i] = new PCB(static_cast<int>(i), tabPag);
            break;
        }
    }

    return true;
}

void GP::desalocaProcesso(int id){
    if(id >= 0 && id < static_cast<int>(processosProntos.size()) && processosProntos[id] != nullptr){
        gm.desaloca(processosProntos[id]->tabPag);
        delete processosProntos[id];
        processosProntos[id];
        processosProntos[id] = nullptr;
    }
}

GP::~GP(){
    for(auto proc : processosProntos){
        delete proc;
    }
}

