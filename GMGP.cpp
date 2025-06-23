#pragma once
#include <iostream>
#include "GMGP.hpp"

extern char debug;

PCB::PCB(int i, int *tabP, int *tabS, string n, int of){
    irpt = noInterrupt;
    nome = n;
    id = i;
    tabPagP = tabP;
    tabPagS = tabS;
    offset = of;
    exec = 1;}

PCB::~PCB(){
    delete tabPagP;
    delete tabPagS;}

ostream &operator<<(ostream &out, PCB &p){
    out << p.id << " " << p.nome;
    return out;}

//===================================//

GM::GM(int tamP, int tamMP, int tamMS){
    tamPag = tamP;
    qntPagP = tamMP/tamP;
    qntPagS = tamMS/tamP;
    clock = 0;
    pagsP = (char*)calloc(qntPagP,sizeof(char));
    usou = (char*)calloc(qntPagS,sizeof(char));
    processosMemS = (PCB**)calloc(qntPagS,sizeof(PCB*));}

GM::~GM(){
    delete pagsP;
    delete usou;
    delete processosMemS;}

int *GM::aloca(int qntIn){
    int tam = qntIn/tamPag + ((qntIn%tamPag) ? 1 : 0);
    int count = tam;
    for(int i = 0; (i < qntPagP) && (count > 0); i++)
        if(pagsP[i] == 0)
            count--;

    if(count > 0) return 0;
    int *tabPag = (int*)malloc((tam+1)*sizeof(int));
    for(int i = 0; count < tam; i++)
        if(pagsP[i] == 0){
            tabPag[++count] = i;
            pagsP[i] = 1;}

    tabPag[0] = tam;
    return tabPag;}

int GM::alocaMemSec(int *pagsS){
    for(int i = 0; i < qntPagS; i++)
        if(pagsS[i] == -1){
            usou[i] = 1;
            return i;}
    while(1){
        if(usou[clock]) usou[clock] = 0;
        else break;
        if(++clock >= qntPagS) clock = 0;}
    if(debug) cout << "Vitimando pag " << clock << endl;
    usou[clock] = 1;
    return clock;}


void GM::desaloca(int *tabP, int *tabS, int *pagsS){
    for(int i = 0; i < tabP[0]; i++){
        pagsP[tabP[i+1]] = 0;
        if(tabS[i] != -1) pagsS[tabS[i]] = -1;}}

//===================================//

GP::GP(Memory *mp, Memory* ms, int tamP, int tamMP, int tamMS){
    tamPag = tamP;
    memP = mp;
    memS = ms;
    pagsS = (int*)malloc((tamMS/tamPag)*sizeof(int));
    for(int i = 0; i < tamMS/tamPag; i++)
        pagsS[i] = -1;
    gm = new GM(tamP, tamMP, tamMS);}

GP::~GP(){
    for(int i = 0; i < prontos.size(); i++)
        if(prontos[i]) 
            delete prontos[i];
    delete pagsS;
    delete gm;}


char GP::criaProcesso(Program *prog){
    if(!prog) return 0;
    int *tabPag = gm->aloca(prog->size);
    if(!tabPag)
        return 0;

    int offset = prog->size%tamPag;
    for(int i = 0; i < tabPag[0]; i++)
        for(int j = 0; j < tamPag; j++){
            if((i == tabPag[0]-1) && (j == offset)) break;
            memP->pos[tabPag[i+1]*tamPag + j] = prog->image[i*tamPag + j];}
    
    int *tabS = (int*)malloc(tabPag[0]*sizeof(int));
    for(int i = 0; i < tabPag[0]; i++)
        tabS[i] = -1;

    prontos.push_back(new PCB(prontos.size()+1, tabPag, tabS, prog->name, offset));
    return 1;}

void GP::alocaMemSecundaria(PCB *p){
    int aux = p->end/tamPag;
    int index = gm->alocaMemSec(pagsS);
    if(gm->processosMemS[index] != nullptr) 
        for(int i = 0; i < gm->processosMemS[index]->tabPagP[0]; i++){
            if(gm->processosMemS[index]->tabPagS[i] == index)
                gm->processosMemS[index]->tabPagS[i] = -1;}

    for(int i = 0; i < tamPag; i++){
        if(pagsS[index] != -1) {
            memP->pos[pagsS[index]*tamPag + i] = memS->pos[index*tamPag + i];}
        memS->pos[index*tamPag + i] = memP->pos[p->tabPagP[aux+1]*tamPag + i];}
    p->tabPagS[aux] = index;
    gm->processosMemS[index] = p;
    pagsS[index] = p->tabPagP[aux+1];}

void GP::desalocaProcesso(int id){
    if(id <= prontos.size() && prontos[id-1]->exec){
        for(int i = 0; i < prontos[id-1]->tabPagP[0]; i++)
            if(prontos[id-1]->tabPagS[i] != -1)
                for(int j = 0; j < tamPag; j++)
                    if(pagsS[prontos[id-1]->tabPagS[i]] != -1){
                        memP->pos[pagsS[prontos[id-1]->tabPagS[i]]*tamPag + j] = memS->pos[prontos[id-1]->tabPagS[i]*tamPag + j];}
        gm->desaloca(prontos[id-1]->tabPagP, prontos[id-1]->tabPagS, pagsS);
        prontos[id-1]->exec = 0;}}