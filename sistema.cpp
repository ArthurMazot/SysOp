#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"
#include "sistema.hpp"

Sistema::Sistema(int tamP, int tamM){
	tamPag = tamP;
	mem = new Memory(tamM);
	hw = new HW(mem, tamP);
	so = new SO(hw, mem, tamP ,tamM);
	hw->cpu->setUtilities(so->utils);
	progs = new Programs();
 	io = new IOGerenciamento();}

Sistema::~Sistema(){
	delete mem;
    delete hw;
    delete so;
    delete progs;
	delete io;}

void Sistema::NEW(string s){//mutex
	if(!so->esc->gp->criaProcesso(progs->retrieveProgram(s)))
		cout << "Não encontrei " << s << endl;
	else cout << s << " Adicionado" << endl;}

void Sistema::rm(int id){ //mutex
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
		for(int j = 0; j < prontos[id-1]->tabPag[0]-1; j++)
			cout << prontos[id-1]->tabPag[j+1] << ", "; 
		cout << prontos[id-1]->tabPag[prontos[id-1]->tabPag[0]] << "]" << endl;
		cout << "Nome: " << prontos[id-1]->nome << endl;
		cout << "Pc: " << prontos[id-1]->pc << endl;
		cout << "regs: [";
		for(int j = 0; j < 9; j++)
			cout << prontos[id-1]->regs[j] << ", "; 
		cout << prontos[id-1]->regs[9] << "]" << endl;
		if(prontos[id-1]->exec)
		for(int j = 0; j < prontos[id-1]->tabPag[0]; j++)
			dumpM(prontos[id-1]->tabPag[j+1]*tamPag, prontos[id-1]->tabPag[j+1]*tamPag + tamPag);
		else cout << "Ja foi desalocado" << endl;}}

void Sistema::dumpM(int inicio, int fim){
	so->utils->dump(inicio, fim);}

void Sistema::execAll(){ //mutex
	vector<PCB*> prontos = so->esc->gp->prontos;
	for(int i = 0; i < prontos.size(); i++)
		if(prontos[i]->exec)
			exec(i+1);}

void Sistema::exec(int id){ //mutex
	vector<PCB*> prontos = so->esc->gp->prontos;
	if(id <= prontos.size() && prontos[id-1]->exec)
		so->esc->addExec(prontos[id-1]);}

void Sistema::traceOn(){
	cout << "traceOn" << endl;
	so->esc->trace = 1;}

void Sistema::traceOff(){
	cout << "traceOff" << endl;
	so->esc->trace = 0;}