#pragma once
#include <iostream>
#include "GMGP.hpp"

GM::GM(int tamP, int tamM){
    tamPag = tamP;
    qntPag = tamM/tamP;
    pags = (char*)calloc(qntPag,sizeof(char));}

GM::~GM(){
    delete pags;}

int *GM::aloca(int qntIn){
    int tam = qntIn/tamPag + ((qntIn%tamPag) ? 1 : 0);
    int count = tam;
    for(int i = 0; (i < qntPag) && (count > 0); i++)
        if(pags[i] == 0)
            count--;

    if(count > 0) return 0;
    int *tabPag = (int*)malloc((tam+1)*sizeof(int));
    for(int i = 0; count < tam; i++)
        if(pags[i] == 0){
            tabPag[++count] = i;
            pags[i] = 1;}

    tabPag[0] = tam;
    return tabPag;}

void GM::desaloca(int *tab){
    for(int i = 0; i < tab[0]; i++){
            pags[tab[i+1]] = 0;}}

//===================================//

PCB::PCB(int i, int *tab, string n, int of){
    nome = n;
    id = i;
    tabPag = tab;
    offset = of;
    exec = 1;}

PCB::~PCB(){
    delete tabPag;}

ostream &operator<<(ostream &out, PCB &p){
    out << p.id << " " << p.nome;
    return out;}

//===================================//

GP::GP(Memory *m, int tamP, int tamM){
    tamPag = tamP;
    mem = m;
    gm = new GM(tamP, tamM);}

GP::~GP(){
    for(int i = 0; i < prontos.size(); i++)
        if(prontos[i]) 
            delete prontos[i];
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
            mem->pos[tabPag[i+1]*tamPag + j] = prog->image[i*tamPag + j];}

    prontos.push_back(new PCB(prontos.size()+1, tabPag, prog->name, offset));
    return 1;}

void GP::desalocaProcesso(int id){
    if(id <= prontos.size() && prontos[id-1]->exec){
        gm->desaloca(prontos[id-1]->tabPag);
        prontos[id-1]->exec = 0;}}