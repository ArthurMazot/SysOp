#pragma once
#include <iostream>
#include "enum.hpp"
using namespace std;

struct Word{
    Opcode opc;
    int ra;
    int rb;
    int p; 
    Word(Opcode=___, int=-1, int=-1, int=-1);
    ~Word();
    void setWord(Opcode, int, int, int);
    void operator=(Word&);
    friend ostream &operator<<(ostream&, Word&);
};

struct Memory{
    int size;
    Word *pos;
    Memory(int);
    ~Memory();
};