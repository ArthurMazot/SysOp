#include "gm.hpp"


GM::GM(int tamM, int tamP){
    tamPag = tamP;
    pags.resize(tamM/ tamPag, false);
}

bool GM::aloca(int numPalavras, vector<int>& tabPag){
    int tam = (numPalavras / tamPag) + ((numPalavras % tamPag) > 0 ? 1 : 0); //quantas paginas o programa precisa
    int count = tam;

    for(size_t i = 0; i < pags.size() && count > 0; i++){ //verfica se tem todas as paginas necessarias
        if(!pags[i])
            count--;
    }

    if(count != 0){ return false; }

    tabPag.clear();
    count = 0;

    for(size_t i = 0; count < tam && i < pags.size(); i++){
        if(!pags[i]){
            pags[i] = true;
            tabPag.push_back(i);
            count++;
        }
    }

    return true;

}

void GM::desaloca(vector<int>& tabPag){
    for(size_t i = 0; i < tabPag.size(); i++){
        if(tabPag[i] >= 0 && tabPag[i] < (int)pags.size()){
            pags[tabPag[i]] = false;
        }
    }
}

