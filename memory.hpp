#pragma once
#include "enum.hpp"

struct Word{
    Opcode opc;
    int ra;
    int rb;
    int p; 
    Word(Opcode=___, int=-1, int=-1, int=-1);
    ~Word();
    void setWord(Opcode, int, int, int);
    void operator=(Word&);
};

struct Memory{
    int size;
    Word *pos;
    Memory(int);
    ~Memory();
};