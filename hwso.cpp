#pragma once
#include <unistd.h>
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"

extern char debug;
extern char flag;

HW::HW(Memory *mp, Memory *ms, int tamPag){
    memP = mp;
    memS = ms;
    cpu = new CPU(ms, tamPag);}

HW::~HW(){
	delete cpu;}

//===================================//

InterruptHandling::InterruptHandling(HW *_hw){
				hw = _hw;}

InterruptHandling::~InterruptHandling(){}

void InterruptHandling::handle(Interrupts irpt, PCB *p){
	cout << "ID: " << p->id << ", Nome: " << p-> nome << " -> Interrupcao " << ((irpt == 1) ? "Endereço invalido " : (irpt == 2) ? "Instrucao Invalida" : "") << endl;
    cout << "PC: " << hw->cpu->pc << endl;}

//===================================//

SysCallHandling::SysCallHandling(HW *_hw){
    hw = _hw;}

SysCallHandling::~SysCallHandling(){}

void SysCallHandling::stop(PCB *p){
    cout << "ID: " << p->id << ", Nome: " << p-> nome << " -> SYSCALL STOP" << endl;}

void SysCallHandling::handle(){
    cout << "SYSCALL pars: " << hw->cpu->reg[8] <<  " / " << hw->cpu->reg[9] << endl;

    switch(hw->cpu->reg[8]){
        case 1: // leitura ...
                break;
        case 2: // escrita - escreve o conteuodo da memoria na posicao dada em reg[9]
                cout << "OUT: " << hw->memP->pos[hw->cpu->reg[9]].p << endl;
                break;
        default: cout << "  PARAMETRO INVALIDO" << endl;}}

//===================================//

Utilities::Utilities(HW *_hw){
	hw = _hw;}

Utilities::~Utilities(){}

void Utilities::loadProgram(Program *p) {
	Word *m = hw->memP->pos;
	for (int i = 0; i < p->size; i++) {
		m[i].opc = p->image[i].opc;
		m[i].ra = p->image[i].ra;
		m[i].rb = p->image[i].rb;
		m[i].p = p->image[i].p;}}

void Utilities::dump(Word &w){
	cout << "[ " << w.opc << ", " << w.ra << ", " << w.rb << ", " << w.p << "]" << endl;}

void Utilities::dump(int ini, int fim){
    Word *m = hw->memP->pos;
    for(int i = ini; i < fim; i++){
        cout << i << ": ";
        dump(m[i]);}}

void Utilities::loadAndExec(Program *p){
    loadProgram(p);
    cout << "---------------------------------- programa carregado na memoria" << endl;
    dump(0, p->size);
    hw->cpu->setContext(0);
    cout << "---------------------------------- inicia execucao " << endl;
    //hw->cpu->run();
    cout << "---------------------------------- memoria após execucao " << endl;
    dump(0, p->size);}

//===================================//

Escalonador::Escalonador(HW *h, Memory *mp, Memory *ms, int tamP, int tamMP, int tamMS, char t){
    trace = t;
    hw = h;
    gp = new GP(mp, ms, tamP, tamMP, tamMS);}

Escalonador::~Escalonador(){
    delete gp;}

void Escalonador::addExec(PCB *p){
    executando.push_back(p);}

void Escalonador::rmExec(int id){
    int i = 0;
    while(executando[i++]->id != id) 
        if(i-1 >= executando.size()) 
            return;
    executando.erase(executando.begin() + i - 1);
    gp->desalocaProcesso(id);}

void Escalonador::addBloq(PCB *p){
    bloqueado.push_back(p);}

void Escalonador::escalonadorRun(){
    int i = 0;
    PCB *p;
    while(flag){
        if(executando.size() <= 0) continue;
        if(i >= executando.size()) i = 0;
        p = executando[i];
        Interrupts irpt = hw->cpu->run(p);
        if(irpt == noInterrupt);
        else if(irpt == IO){
            addBloq(p);
            executando.erase(executando.begin() + i);}
        else if(irpt == pageFault){
            addBloq(p);
            executando.erase(executando.begin() + i);}
        else rmExec(executando[i]->id);
        i++;}}

void Escalonador::pageFaultRun(){
    int i = 0;
    PCB *p;
    while(flag){
        if(bloqueado.size() <= 0) continue;
        if(i >= bloqueado.size()) i = 0;
        p = bloqueado[i];
        if(p->irpt == pageFault){
            if(debug) cout << "Tratando PageFault do " << p->nome << endl;
            gp->alocaMemSecundaria(p);
            p->irpt = noInterrupt;
            executando.push_back(p);
            for(int j = 0; j < bloqueado.size(); j++)
                if(p->id == bloqueado[j]->id){
                    bloqueado.erase(bloqueado.begin() + j);
                    break;}}
        i++;}}

void Escalonador::IORun(){
    int i = 0;
    PCB *p;
    while(flag){
        if(bloqueado.size() <= 0) continue;
        if(i >= bloqueado.size()) i = 0;
        p = bloqueado[i];
        if(p->irpt == IO){
            if(debug) cout << "Tratando IO do " << p->nome << endl;
            //gp->alocaMemSecundaria(p);
            p->irpt = noInterrupt;
            executando.push_back(p);
            for(int j = 0; j < bloqueado.size(); j++)
                if(p->id == bloqueado[j]->id){
                    bloqueado.erase(bloqueado.begin() + j);
                    break;}}
        i++;}}


//===================================//

SO::SO(HW *hw, Memory *memP, Memory *memS, int tamP, int tamMP, int tamMS){
    esc = new Escalonador(hw, memP, memS, tamP, tamMP, tamMS, true);
	ih = new InterruptHandling(hw);
	sc = new SysCallHandling(hw);
	hw->cpu->setAddressOfHandlers(ih, sc);
	utils = new Utilities(hw);}

SO::~SO(){
    delete esc;
	delete ih;
	delete sc;
	delete utils;}