#include <iostream>
using namespace std;

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

		Word(Opcode _opc, int _ra, int _rb, int _p){
			opc = _opc;
			ra = _ra;
			rb = _rb;
			p  = _p;}

        Word(){
            opc = ___;
			ra = -1;
			rb = -1;
			p  = -1;}

        ~Word(){}
};

struct Memory{
    int size;
    Word **pos;

    Memory(int s){
        size = s;
        pos = (Word**)malloc(size*sizeof(Word*));}
    
    ~Memory(){
        for(int i = 0; i < size; i++)
            if(pos[i])
                delete pos[i];
        delete pos;}
};