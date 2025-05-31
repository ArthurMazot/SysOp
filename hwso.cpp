#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"
#include "IO.hpp"
#include <mutex>

extern char flag;

extern GP*   gp;        
extern CPU*  cpu;          
extern PCB*  currentPCB;   

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
	cout << "Interrupcao " << irpt << endl << "pc: " << hw->cpu->pc << endl;}

//===================================//

SysCallHandling::SysCallHandling(HW *_hw){
    hw = _hw;}

SysCallHandling::~SysCallHandling(){}

void SysCallHandling::stop(){
    cout << "SYSCALL STOP" << endl;}

void SysCallHandling::handle() {
    PCB* proc = currentPCB;
    if (!proc) {
        std::cerr << "[SysCallHandling] Aviso: currentPCB == nullptr\n";
        return;
    }
    int syscallType = hw->cpu->reg[8];   // 1 = IN (leitura), 2 = OUT (escrita)
    int virtualAddr = hw->cpu->reg[9];
    int physicalAddr = hw->cpu->logicoFisico(virtualAddr, proc);
    
    IO req;
    req.pid = proc->id;
    if (syscallType == 1) {
        // leitura (IN)
        req.type = ioType::READ;
    }
    else if (syscallType == 2) {
        req.type  = ioType::WRITE;
        req.valueType = hw->cpu->reg[10];
    }
    else {
        std::cerr << "[SysCallHandling] Parâmetro inválido em SYSCALL: "<< syscallType << "\n";
        return;
    }
    req.address = physicalAddr;
    {
        std::lock_guard<mutex> lk(ioMutex);
        ioQueue.push(req);
    }
    ioCv.notify_one();
    proc->state = BLOCKED;
    {
        auto& rQ = gp->readyQueue;
        auto& bQ = gp->blockedQueue;
        auto  it = std::find(rQ.begin(), rQ.end(), proc);
        if (it != rQ.end()) {
            rQ.erase(it);
            bQ.push_back(proc);
        }
    }
    hw->cpu->irpt = intSysCall;
}
    

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

void Escalonador::escalonadorRun() {
    while (flag) {
        if (gp->readyQueue.empty()) {
            continue;
        }
        PCB* p = gp->readyQueue.front();
        gp->readyQueue.pop_front();
        p->state = RUNNING;
    
        currentPCB = p;
        int result = hw->cpu->run(p);
        currentPCB = nullptr;

        if (result == 0) {
            if (p->state == RUNNING) {
                p->state = READY;
                gp->readyQueue.push_back(p);
            }
        }
        else if (result == 1) {
            if (p->state == RUNNING) {
                p->state = TERMINATED;
                gp->desalocaProcesso(p->id);
            }
        }
        else if (result == 2) {
            p->state = TERMINATED;
            gp->desalocaProcesso(p->id);
        }
    }
}
    
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