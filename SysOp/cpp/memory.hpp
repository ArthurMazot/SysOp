#pragma once

enum Opcode : int{
    ___, DATA,
    JMP, JMPI, JMPIG, JMPIL, JMPIE,
    JMPIM, JMPIGM, JMPILM, JMPIEM,
    JMPIGK, JMPILK, JMPIEK, JMPIGT,
    ADDI, SUBI, ADD, SUB, MULT,
    LDI, LDD, STD, LDX, STX, MOVE,
    SYSCALL, STOP};

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