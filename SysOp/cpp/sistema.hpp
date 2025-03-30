#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "enum.hpp"

struct Sistema{
    HW *hw;
	SO *so;
	Programs *progs;
	Sistema(int);
    ~Sistema();
	void run();
};