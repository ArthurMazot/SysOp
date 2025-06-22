#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"
#include "IO.hpp"

class HW;
class SO;
class IOGerenciamento;

struct Sistema{
	int tamPag;
	Memory *mem;
    HW *hw;
	SO *so;
	Programs *progs;
	IOGerenciamento *io;
	Sistema(int, int);
    ~Sistema();
	void NEW(string);
	void rm(int);
	void ps();
	void dump(int);
	void dumpM(int, int);
	void exec(int);
	void execAll();
	void traceOn();
	void traceOff();
};