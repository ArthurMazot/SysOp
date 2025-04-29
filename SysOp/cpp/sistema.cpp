#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"
#include "sistema.hpp"

Sistema::Sistema(int tamP, int tamM){
	tamMem = tamM;
	mem = new Memory(tamMem);
	gp = new GP(mem, tamP, tamM);
	hw = new HW(tamM, tamP, gp, mem);
	so = new SO(hw, tamP ,tamM , gp);
	hw->cpu->setUtilities(so->utils);
	progs = new Programs();}

Sistema::~Sistema(){
	delete gp;
    delete hw;
    delete so;
    delete progs;}

void Sistema::NEW(string s){
	if(!so->gp->criaProcesso(progs->retrieveProgram(s)))
		cout << "Não encontrei " << s << endl;
	else cout << s << " Adicionado" << endl;}

void Sistema::rm(int id){
	hw->cpu->rmExec(id);
	so->gp->desalocaProcesso(id);}

void Sistema::ps(){
	cout << "ID | Nome" << endl;
	vector<PCB*> prontos = so->gp->prontos;
	for(int i = 0; i < prontos.size(); i++)
		if(prontos[i]->exec)
			cout << *prontos[i] << endl;}

void Sistema::dump(int id){
	vector<PCB*> prontos = so->gp->prontos;
	if(id <= prontos.size()){
		cout << "ID: " << id << endl;
		cout << "tabPag: [";
		for(int j = 1; j < prontos[id-1]->tabPag[0]-1; j++)
			cout << prontos[id-1]->tabPag[j] << ", "; 
		cout << prontos[id-1]->tabPag[prontos[id-1]->tabPag[0]-1] << "]" << endl;
		cout << "Nome: " << prontos[id-1]->nome << endl;
		cout << "Pc: " << prontos[id-1]->pc << endl;
		cout << "regs: [";
		for(int j = 0; j < 9; j++)
			cout << prontos[id-1]->regs[j] << ", "; 
		cout << prontos[id-1]->regs[9] << "]" << endl;
		if(prontos[id-1]->exec)
		for(int j = 1; j < prontos[id-1]->tabPag[0]; j++)
			dumpM(prontos[id-1]->tabPag[j]*so->gp->tamPag, prontos[id-1]->tabPag[j]*so->gp->tamPag + so->gp->tamPag);
		else cout << "Ja foi desalocado" << endl;}}

void Sistema::dumpM(int inicio, int fim){
	so->utils->dump(inicio, fim);}

void Sistema::execAll(){
	vector<PCB*> prontos = so->gp->prontos;
	for(int i = 0; i < prontos.size(); i++)
		if(prontos[i]->exec)
			exec(i+1);}

void Sistema::exec(int id){
	vector<PCB*> prontos = so->gp->prontos;
	if(id <= prontos.size() && prontos[id-1]->exec)
		hw->cpu->addExec(prontos[id-1]);}

void Sistema::traceOn(){
	cout << "traceOn" << endl;
	hw->cpu->debug = 1;}

void Sistema::traceOff(){
	cout << "traceOff" << endl;
	hw->cpu->debug = 0;}