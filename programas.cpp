#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "enum.hpp"

Program::Program(int s, string n, Word *i){
    size = s;
    name = n;
    image = i;}

Program::~Program(){
    delete image;}

//===================================//

Programs::Programs(){
    size = 8;
    progs = (Program**)malloc(size*sizeof(Program*));
    Word *aux = (Word*)malloc(11*sizeof(Word));

    aux[0].setWord(LDI, 0, -1, 7); 
    aux[1].setWord(LDI, 1, -1, 1);
    aux[2].setWord(LDI, 6, -1, 1);
    aux[3].setWord(LDI, 7, -1, 8);
    aux[4].setWord(JMPIE, 7, 0, 0);
    aux[5].setWord(MULT, 1, 0, -1);
    aux[6].setWord(SUB, 0, 6, -1);
    aux[7].setWord(JMP, -1, -1, 4);
    aux[8].setWord(STD, 1, -1, 10);
    aux[9].setWord(STOP, -1, -1, -1);
    aux[10].setWord(DATA, -1, -1, -1);
    progs[0] = new Program(11 ,"fatorial", aux); //programa 1

    aux = (Word*)malloc(20*sizeof(Word));
    aux[0].setWord(LDI, 0, -1, 5);
    aux[1].setWord(STD, 0, -1, 19);
    aux[2].setWord(LDD, 0, -1, 19);
    aux[3].setWord(LDI, 1, -1, -1);
    aux[4].setWord(LDI, 2, -1, 13);
    aux[5].setWord(JMPIL, 2, 0, -1);
    aux[6].setWord(LDI, 1, -1, 1);
    aux[7].setWord(LDI, 6, -1, 1);
    aux[8].setWord(LDI, 7, -1, 13);
    aux[9].setWord(JMPIE, 7, 0, 0);
    aux[10].setWord(MULT, 1, 0, -1);
    aux[11].setWord(SUB, 0, 6, -1);
    aux[12].setWord(JMP, -1, -1, 9);
    aux[13].setWord(STD, 1, -1, 18);
    aux[14].setWord(LDI, 8, -1, 2);
    aux[15].setWord(LDI, 9, -1, 18);
    aux[16].setWord(SYSCALL, -1, -1, -1);
    aux[17].setWord(STOP, -1, -1, -1);
    aux[18].setWord(DATA, -1, -1, -1);
    aux[19].setWord(DATA, -1, -1, -1);
    progs[1] = new Program(20 ,"fatorialV2", aux); //programa 2

    aux = (Word*)malloc(14*sizeof(Word));
    aux[0].setWord(LDI, 0, -1, 999);
    aux[1].setWord(STD, 0, -1, 8);
    aux[2].setWord(STD, 0, -1, 9);
    aux[3].setWord(STD, 0, -1, 10);
    aux[4].setWord(STD, 0, -1, 11);
    aux[5].setWord(STD, 0, -1, 12);
    aux[6].setWord(STOP, -1, -1, -1);
    aux[7].setWord(DATA, -1, -1, -1);
    aux[8].setWord(DATA, -1, -1, -1);
    aux[9].setWord(DATA, -1, -1, -1);
    aux[10].setWord(DATA, -1, -1, -1);
    aux[11].setWord(DATA, -1, -1, -1);
    aux[12].setWord(DATA, -1, -1, -1);
    aux[13].setWord(DATA, -1, -1, -1);
    progs[2] = new Program(14, "progMinimo", aux); //programa 3

    aux = (Word*)malloc(30*sizeof(Word));
    aux[0].setWord(LDI, 1, -1, 0);
    aux[1].setWord(STD, 1, -1, 20);
    aux[2].setWord(LDI, 2, -1, 1);
    aux[3].setWord(STD, 2, -1, 21);
    aux[4].setWord(LDI, 0, -1, 22);
    aux[5].setWord(LDI, 6, -1, 6);
    aux[6].setWord(LDI, 7, -1, 31);
    aux[7].setWord(LDI, 3, -1, 0);
    aux[8].setWord(ADD, 3, 1, -1);
    aux[9].setWord(LDI, 1, -1, 0);
    aux[10].setWord(ADD, 1, 2, -1);
    aux[11].setWord(ADD, 2, 3, -1);
    aux[12].setWord(STX, 0, 2, -1);
    aux[13].setWord(ADDI, 0, -1, 1);
    aux[14].setWord(SUB, 7, 0, -1);
    aux[15].setWord(JMPIG, 6, 7, -1);
    aux[16].setWord(STOP, -1, -1, -1);
    aux[17].setWord(DATA, -1, -1, -1);
    aux[18].setWord(DATA, -1, -1, -1);
    aux[19].setWord(DATA, -1, -1, -1);
    aux[20].setWord(DATA, -1, -1, -1);
    aux[21].setWord(DATA, -1, -1, -1);
    aux[22].setWord(DATA, -1, -1, -1);
    aux[23].setWord(DATA, -1, -1, -1);
    aux[24].setWord(DATA, -1, -1, -1);
    aux[25].setWord(DATA, -1, -1, -1);
    aux[26].setWord(DATA, -1, -1, -1);
    aux[27].setWord(DATA, -1, -1, -1);
    aux[28].setWord(DATA, -1, -1, -1);
    aux[29].setWord(DATA, -1, -1, -1);
    progs[3] = new Program(30, "fibonacci10", aux); //programa 4

    aux = (Word*)malloc(32*sizeof(Word));
    aux[0].setWord(LDI, 1, -1, 0);
    aux[1].setWord(STD, 1, -1, 20);
    aux[2].setWord(LDI, 2, -1, 1);
    aux[3].setWord(STD, 2, -1, 21);
    aux[4].setWord(LDI, 0, -1, 22);
    aux[5].setWord(LDI, 6, -1, 6);
    aux[6].setWord(LDI, 7, -1, 31);
    aux[7].setWord(MOVE, 3, 1, -1);
    aux[8].setWord(MOVE, 1, 2, -1);
    aux[9].setWord(ADD, 2, 3, -1);
    aux[10].setWord(STX, 0, 2, -1);
    aux[11].setWord(ADDI, 0, -1, 1);
    aux[12].setWord(SUB, 7, 0, -1);
    aux[13].setWord(JMPIG, 6, 7, -1);
    aux[14].setWord(STOP, -1, -1, -1);
    aux[15].setWord(DATA, -1, -1, -1);
    aux[16].setWord(DATA, -1, -1, -1);
    aux[17].setWord(DATA, -1, -1, -1);
    aux[18].setWord(DATA, -1, -1, -1);
    aux[19].setWord(DATA, -1, -1, -1);
    aux[20].setWord(DATA, -1, -1, -1);
    aux[21].setWord(DATA, -1, -1, -1);
    aux[22].setWord(DATA, -1, -1, -1);
    aux[23].setWord(DATA, -1, -1, -1);
    aux[24].setWord(DATA, -1, -1, -1);
    aux[25].setWord(DATA, -1, -1, -1);
    aux[26].setWord(DATA, -1, -1, -1);
    aux[27].setWord(DATA, -1, -1, -1);
    aux[28].setWord(DATA, -1, -1, -1);
    aux[29].setWord(DATA, -1, -1, -1);
    aux[30].setWord(DATA, -1, -1, -1);
    aux[31].setWord(DATA, -1, -1, -1);
    progs[4] = new Program(32, "fibonacci10v2", aux); //programa 5

    aux = (Word*)malloc(57*sizeof(Word));
    aux[0].setWord(LDI, 8, -1, 1);
	aux[1].setWord(LDI, 9, -1, 55);
	aux[2].setWord(SYSCALL, -1, -1, -1);
	aux[3].setWord(LDD, 7, -1, 55);
	aux[4].setWord(LDI, 3, -1, 0);
	aux[5].setWord(ADD, 3, 7, -1);
	aux[6].setWord(LDI, 4, -1, 36);
	aux[7].setWord(LDI, 1, -1, -1);
	aux[8].setWord(STD, 1, -1, 41);
	aux[9].setWord(JMPIL, 4, 7, -1);
	aux[10].setWord(JMPIE, 4, 7, -1);
	aux[11].setWord(ADDI, 7, -1, 41);
	aux[12].setWord(LDI, 1, -1, 0);
	aux[13].setWord(STD, 1, -1, 41);
	aux[14].setWord(SUBI, 3, -1, 1);
	aux[15].setWord(JMPIE, 4, 3, -1);
	aux[16].setWord(ADDI, 3, -1, 1);
	aux[17].setWord(LDI, 2, -1, 1);
	aux[18].setWord(STD, 2, -1, 42);
	aux[19].setWord(SUBI, 3, -1, 2);
	aux[20].setWord(JMPIE, 4, 3, -1);
	aux[21].setWord(LDI, 0, -1, 43);
	aux[22].setWord(LDI, 6, -1, 25);
	aux[23].setWord(LDI, 5, -1, 0);
	aux[24].setWord(ADD, 5, 7, -1);
	aux[25].setWord(LDI, 7, -1, 0);
	aux[26].setWord(ADD, 7, 5, -1);
	aux[27].setWord(LDI, 3, -1, 0);
	aux[28].setWord(ADD, 3, 1, -1);
	aux[29].setWord(LDI, 1, -1, 0);
	aux[30].setWord(ADD, 1, 2, -1);
	aux[31].setWord(ADD, 2, 3, -1);
	aux[32].setWord(STX, 0, 2, -1);
	aux[33].setWord(ADDI, 0, -1, 1);
	aux[34].setWord(SUB, 7, 0, -1);
	aux[35].setWord(JMPIG, 6, 7, -1);
	aux[36].setWord(STOP, -1, -1, -1);
	aux[37].setWord(DATA, -1, -1, -1);
	aux[38].setWord(DATA, -1, -1, -1);
	aux[39].setWord(DATA, -1, -1, -1);
	aux[40].setWord(DATA, -1, -1, -1);
	aux[41].setWord(DATA, -1, -1, -1);
	aux[42].setWord(DATA, -1, -1, -1);
	aux[43].setWord(DATA, -1, -1, -1);
	aux[44].setWord(DATA, -1, -1, -1);
	aux[45].setWord(DATA, -1, -1, -1);
	aux[46].setWord(DATA, -1, -1, -1);
	aux[47].setWord(DATA, -1, -1, -1);
	aux[48].setWord(DATA, -1, -1, -1);
	aux[49].setWord(DATA, -1, -1, -1);
	aux[50].setWord(DATA, -1, -1, -1);
	aux[51].setWord(DATA, -1, -1, -1);
	aux[52].setWord(DATA, -1, -1, -1);
	aux[53].setWord(DATA, -1, -1, -1);
	aux[54].setWord(DATA, -1, -1, -1);
	aux[55].setWord(DATA, -1, -1, -1);
	aux[56].setWord(DATA, -1, -1, -1);
    progs[5] = new Program(57, "fibonacciREAD", aux); //programa 6

    aux = (Word*)malloc(16*sizeof(Word));
    aux[0].setWord(LDI, 0, -1, 7);
	aux[1].setWord(STD, 0, -1, 50);
	aux[2].setWord(LDD, 0, -1, 50);
	aux[3].setWord(LDI, 1, -1, -1);
	aux[4].setWord(LDI, 2, -1, 13);
	aux[5].setWord(JMPIL, 2, 0, -1);
	aux[6].setWord(LDI, 1, -1, 1);
	aux[7].setWord(LDI, 6, -1, 1);
	aux[8].setWord(LDI, 7, -1, 13);
	aux[9].setWord(JMPIE, 7, 0, 0);
	aux[10].setWord(MULT, 1, 0, -1);
	aux[11].setWord(SUB, 0, 6, -1);
	aux[12].setWord(JMP, -1, -1, 9);
	aux[13].setWord(STD, 1, -1, 15);
	aux[14].setWord(STOP, -1, -1, -1);
	aux[15].setWord(DATA, -1, -1, -1);
    progs[6] = new Program(16, "PB", aux);

    aux = (Word*)malloc(54*sizeof(Word)); //programa 7
    aux[0].setWord(LDI, 7, -1, 5);
	aux[1].setWord(LDI, 6, -1, 5);
	aux[2].setWord(LDI, 5, -1, 46);
	aux[3].setWord(LDI, 4, -1, 47);
	aux[4].setWord(LDI, 0, -1, 4);
	aux[5].setWord(STD, 0, -1, 46);
	aux[6].setWord(LDI, 0, -1, 3);
	aux[7].setWord(STD, 0, -1, 47);
	aux[8].setWord(LDI, 0, -1, 5);
	aux[9].setWord(STD, 0, -1, 48);
	aux[10].setWord(LDI, 0, -1, 1);
	aux[11].setWord(STD, 0, -1, 49);
	aux[12].setWord(LDI, 0, -1, 2);
	aux[13].setWord(STD, 0, -1, 50);
	aux[14].setWord(LDI, 3, -1, 25);
	aux[15].setWord(STD, 3, -1, 99);
	aux[16].setWord(LDI, 3, -1, 22);
	aux[17].setWord(STD, 3, -1, 98);
	aux[18].setWord(LDI, 3, -1, 38);
	aux[19].setWord(STD, 3, -1, 97);
	aux[20].setWord(LDI, 3, -1, 25);
	aux[21].setWord(STD, 3, -1, 96);
	aux[22].setWord(LDI, 6, -1, 0);
	aux[23].setWord(ADD, 6, 7, -1);
	aux[24].setWord(SUBI, 6, -1, 1);
	aux[25].setWord(JMPIEM, -1, 6, 97);
	aux[26].setWord(LDX, 0, 5, -1);
	aux[27].setWord(LDX, 1, 4, -1);
	aux[28].setWord(LDI, 2, -1, 0);
	aux[29].setWord(ADD, 2, 0, -1);
	aux[30].setWord(SUB, 2, 1, -1);
	aux[31].setWord(ADDI, 4, -1, 1);
	aux[32].setWord(SUBI, 6, -1, 1);
	aux[33].setWord(JMPILM, -1, 2, 99);
	aux[34].setWord(STX, 5, 1, -1);
	aux[35].setWord(SUBI, 4, -1, 1);
	aux[36].setWord(STX, 4, 0, -1);
	aux[37].setWord(ADDI, 4, -1, 1);
	aux[38].setWord(JMPIGM, -1, 6, 99);
	aux[39].setWord(ADDI, 5, -1, 1);
	aux[40].setWord(SUBI, 7, -1, 1);
	aux[41].setWord(LDI, 4, -1, 0);
	aux[42].setWord(ADD, 4, 5, -1);
	aux[43].setWord(ADDI, 4, -1, 1);
	aux[44].setWord(JMPIGM, -1, 7, 98);
	aux[45].setWord(STOP, -1, -1, -1);
	aux[46].setWord(DATA, -1, -1, -1);
	aux[47].setWord(DATA, -1, -1, -1);
	aux[48].setWord(DATA, -1, -1, -1);
	aux[49].setWord(DATA, -1, -1, -1);
	aux[50].setWord(DATA, -1, -1, -1);
	aux[51].setWord(DATA, -1, -1, -1);
	aux[52].setWord(DATA, -1, -1, -1);
	aux[53].setWord(DATA, -1, -1, -1);
    progs[7] = new Program(54, "PC", aux);} //programa 8

Programs::~Programs(){
    for(int i = 0; i < size; i++)
        if(progs[i])
            delete progs[i];
        delete progs;}

Program *Programs::retrieveProgram(string pname){
    for(int i = 0; i < size; i++)
        if (progs[i] && progs[i]->name == pname)
            return progs[i];
    return nullptr;}
