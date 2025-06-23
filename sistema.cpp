#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"
#include "sistema.hpp"

Sistema::Sistema(int tamP, int tamMP, int tamMS){
	tamPag = tamP;
	memP = new Memory(tamMP);
	memS = new Memory(tamMS);
	hw = new HW(memP, memS, tamP);
	so = new SO(hw, memP, memS, tamP ,tamMP, tamMS);
	hw->cpu->setUtilities(so->utils);
	progs = new Programs();
	hw->cpu->usou = so->esc->gp->gm->usou;}

Sistema::~Sistema(){
	delete memP;
	delete memS;
    delete hw;
    delete so;
    delete progs;}

void Sistema::NEW(string s){
	if(!so->esc->gp->criaProcesso(progs->retrieveProgram(s)))
		cout << "Não encontrei " << s << endl;
	else cout << s << " Adicionado" << endl;}

void Sistema::rm(int id){
	so->esc->gp->desalocaProcesso(id);}

void Sistema::ps(){
	cout << "ID | Nome" << endl;
	vector<PCB*> prontos = so->esc->gp->prontos;
	for(int i = 0; i < prontos.size(); i++)
		if(prontos[i]->exec)
			cout << *prontos[i] << endl;}

void Sistema::dump(int id){
	vector<PCB*> prontos = so->esc->gp->prontos;
	if(id <= prontos.size()){
		cout << "ID: " << id << endl;
		cout << "tabPag: [";
		for(int j = 0; j < prontos[id-1]->tabPagP[0]-1; j++)
			cout << prontos[id-1]->tabPagP[j+1] << ", "; 
		cout << prontos[id-1]->tabPagP[prontos[id-1]->tabPagP[0]] << "]" << endl;
		cout << "Nome: " << prontos[id-1]->nome << endl;
		cout << "Pc: " << prontos[id-1]->pc << endl;
		cout << "regs: [";
		for(int j = 0; j < 9; j++)
			cout << prontos[id-1]->regs[j] << ", "; 
		cout << prontos[id-1]->regs[9] << "]" << endl;

		cout << "Disco" << endl;
		for(int j = 0; j < prontos[id-1]->tabPagP[0]; j++)
			dumpMP(prontos[id-1]->tabPagP[j+1]*tamPag, prontos[id-1]->tabPagP[j+1]*tamPag + tamPag);
		cout << "==============================" << endl;
		cout << "Memória Principal" << endl;
		for(int j = 0; j < prontos[id-1]->tabPagP[0]; j++)
			if(prontos[id-1]->tabPagS[j] != -1)
				dumpMP(prontos[id-1]->tabPagS[j]*tamPag, prontos[id-1]->tabPagS[j]*tamPag + tamPag);
		}}

void Sistema::dumpD(int inicio, int fim){
	while(inicio < fim) cout << inicio << ": " << memP->pos[inicio++] << endl;}

void Sistema::dumpMP(int inicio, int fim){
	while(inicio < fim) cout << inicio << ": " << memS->pos[inicio++] << endl;}

void Sistema::execAll(){
	vector<PCB*> prontos = so->esc->gp->prontos;
	for(int i = 0; i < prontos.size(); i++)
		if(prontos[i]->exec)
			exec(i+1);}

void Sistema::exec(int id){
	vector<PCB*> prontos = so->esc->gp->prontos;
	if(id <= prontos.size() && prontos[id-1]->exec)
		so->esc->addExec(prontos[id-1]);}