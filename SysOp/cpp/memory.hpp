#pragma once
#include "enum.hpp"

struct Word{
    Opcode opc;
    int ra;
    int rb;
    int p; 
    Word(Opcode, int, int, int);
    Word();
    ~Word();
    void operator=(Word&);
};

struct Memory{
    int size;
    Word *pos;
    Memory(int);
    ~Memory();
};