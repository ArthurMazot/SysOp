#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"
#include "sistema.hpp"

Sistema::Sistema(int tamMem){
	hw = new HW(tamMem);
	so = new SO(hw);
	hw->cpu->setUtilities(so->utils);
	progs = new Programs();}

Sistema::~Sistema(){
    delete hw;
    delete so;
    delete progs;}

void Sistema::run(){
	so->utils->loadAndExec(progs->retrieveProgram("fatorialV2"));}