#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"

HW::HW(int tamMem){
			mem = new Memory(tamMem);
			cpu = new CPU(mem, true);}

HW::~HW(){
	delete mem;
	delete cpu;}

//===================================//

InterruptHandling::InterruptHandling(HW *_hw){
				hw = _hw;}

InterruptHandling::~InterruptHandling(){}

void InterruptHandling::handle(Interrupts irpt){
	cout << "Interrupcao " << irpt << "pc: " << hw->cpu->pc << endl;}

//===================================//

SysCallHandling::SysCallHandling(HW *_hw){
    hw = _hw;}

SysCallHandling::~SysCallHandling(){}

void SysCallHandling::stop(){
    cout << "SYSCALL STOP" << endl;}

void SysCallHandling::handle(){
    cout << "SYSCALL pars: " << hw->cpu->reg[8] <<  " / " << hw->cpu->reg[9] << endl;

    switch(hw->cpu->reg[8]){
        case 1: // leitura ...
                break;
        case 2: // escrita - escreve o conteuodo da memoria na posicao dada em reg[9]
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
		m[i].opc = p->image[i]->opc;
		m[i].ra = p->image[i]->ra;
		m[i].rb = p->image[i]->rb;
		m[i].p = p->image[i]->p;}}

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
    hw->cpu->run();
    cout << "---------------------------------- memoria após execucao " << endl;
    dump(0, p->size);}

//===================================//

SO::SO(HW *hw){
	ih = new InterruptHandling(hw);
	sc = new SysCallHandling(hw);
	hw->cpu->setAddressOfHandlers(ih, sc);
	utils = new Utilities(hw);}

SO::~SO(){
	delete ih;
	delete sc;
	delete utils;}