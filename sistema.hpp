#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"

struct Sistema{
	int tamPag;
	Memory *memP;
	Memory *memS;
    HW *hw;
	SO *so;
	Programs *progs;
	Sistema(int, int, int);
    ~Sistema();
	void NEW(string);
	void rm(int);
	void ps();
	void dump(int);
	void dumpMP(int, int);
	void dumpMS(int, int);
	void exec(int);
	void execAll();
};