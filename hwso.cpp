#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"

extern char flag;

HW::HW(Memory *m, int tamPag){
		mem = m;
		cpu = new CPU(mem, false, tamPag);}

HW::~HW(){
	delete cpu;}

//===================================//

InterruptHandling::InterruptHandling(HW *_hw){
				hw = _hw;}

InterruptHandling::~InterruptHandling(){}

void InterruptHandling::handle(Interrupts irpt){
	cout << "Interrupcao " << irpt << endl << "pc: " << hw->cpu->pc << endl;
    if (irpt == Interrupts::IOInterrupt) {
        sistema->io->finalizarInterrupcao();
    }
}

//===================================//

SysCallHandling::SysCallHandling(HW *_hw){
    hw = _hw;}

SysCallHandling::~SysCallHandling(){}

void SysCallHandling::stop(){
    cout << "SYSCALL STOP" << endl;}

void SysCallHandling::handle(){
    int code = hw->cpu->reg[8];
    int addr = hw->cpu->reg[9];
    PCB* p;
    cout << "SYSCALL pars: " << hw->cpu->reg[8] <<  " / " << hw->cpu->reg[9] << endl;

    switch(code){
        case 1: // leitura ...
            sistema->io->adicionaReq(p, LEITURA, addr);
            break;
        case 2: // escrita - escreve o conteuodo da memoria na posicao dada em reg[9]
            sistema->io->adicionaReq(p, ESCRITA, addr);    
            cout << "OUT: " << hw->mem->pos[hw->cpu->reg[9]].p << endl;
            break;
        default: cout << "  PARAMETRO INVALIDO" << endl;}}

//===================================//

Utilities::Utilities(HW *_hw){
	hw = _hw;}

Utilities::~Utilities(){}

void Utilities::loadProgram(Program *p) {
	Word *m = hw->mem->pos;
	for (int i = 0; i < p->size; i++) {
		m[i].opc = p->image[i].opc;
		m[i].ra = p->image[i].ra;
		m[i].rb = p->image[i].rb;
		m[i].p = p->image[i].p;}}

void Utilities::dump(Word &w){
	cout << "[ " << w.opc << ", " << w.ra << ", " << w.rb << ", " << w.p << "]" << endl;}

void Utilities::dump(int ini, int fim){
    Word *m = hw->mem->pos;
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

Escalonador::Escalonador(HW *h, Memory *m, int tamP, int tamM, char t){
    trace = t;
    hw = h;
    gp = new GP(m, tamP, tamM);}

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

void Escalonador::escalonadorRun(){
    int i = 0;
    while(flag){
        if(executando.size() <= 0) continue;
        if(i >= executando.size()) i = 0;
        cout << "Trocando para " << executando[i]->nome << endl;
        if(hw->cpu->run(executando[i])) rmExec(executando[i]->id);
        i++;}}

//===================================//

SO::SO(HW *hw, Memory *m, int tamP, int tamM){
    esc = new Escalonador(hw, m, tamP, tamM, true);
	ih = new InterruptHandling(hw);
	sc = new SysCallHandling(hw);
	hw->cpu->setAddressOfHandlers(ih, sc);
	utils = new Utilities(hw);}

SO::~SO(){
    delete esc;
	delete ih;
	delete sc;
	delete utils;}