#pragma once
#include "memory.hpp"
#include "programas.hpp"
#include "enum.hpp"

Program::Program(int s, string n, Word **i){
    size = s;
    name = n;
    image = i;}

Program::~Program(){
    for(int i = 0; i < size; i++)
        if(image[i])
            delete image[i];
    delete image;}

//===================================//

Programs::Programs(){
    size = 8;
    progs = (Program**)malloc(size*sizeof(Program*));
    Word **aux = (Word**)malloc(11*sizeof(Word*));

    aux[0] = new Word(LDI, 0, -1, 7); 
    aux[1] = new Word(LDI, 1, -1, 1);
    aux[2] = new Word(LDI, 6, -1, 1);
    aux[3] = new Word(LDI, 7, -1, 8);
    aux[4] = new Word(JMPIE, 7, 0, 0);
    aux[5] = new Word(MULT, 1, 0, -1);
    aux[6] = new Word(SUB, 0, 6, -1);
    aux[7] = new Word(JMP, -1, -1, 4);
    aux[8] = new Word(STD, 1, -1, 10);
    aux[9] = new Word(STOP, -1, -1, -1);
    aux[10] = new Word(DATA, -1, -1, -1);
    progs[0] = new Program(11 ,"fatorial", aux); //programa 1

    aux = (Word**)malloc(20*sizeof(Word*));
    aux[0] = new Word(LDI, 0, -1, 5);
    aux[1] = new Word(STD, 0, -1, 19);
    aux[2] = new Word(LDD, 0, -1, 19);
    aux[3] = new Word(LDI, 1, -1, -1);
    aux[4] = new Word(LDI, 2, -1, 13);
    aux[5] = new Word(JMPIL, 2, 0, -1);
    aux[6] = new Word(LDI, 1, -1, 1);
    aux[7] = new Word(LDI, 6, -1, 1);
    aux[8] = new Word(LDI, 7, -1, 13);
    aux[9] = new Word(JMPIE, 7, 0, 0);
    aux[10] = new Word(MULT, 1, 0, -1);
    aux[11] = new Word(SUB, 0, 6, -1);
    aux[12] = new Word(JMP, -1, -1, 9);
    aux[13] = new Word(STD, 1, -1, 18);
    aux[14] = new Word(LDI, 8, -1, 2);
    aux[15] = new Word(LDI, 9, -1, 18);
    aux[16] = new Word(SYSCALL, -1, -1, -1);
    aux[17] = new Word(STOP, -1, -1, -1);
    aux[18] = new Word(DATA, -1, -1, -1);
    aux[19] = new Word(DATA, -1, -1, -1);
    progs[1] = new Program(19 ,"fatorialV2", aux); //programa 2

    aux = (Word**)malloc(14*sizeof(Word*));
    aux[0] = new Word(LDI, 0, -1, 999);
    aux[1] = new Word(STD, 0, -1, 8);
    aux[2] = new Word(STD, 0, -1, 9);
    aux[3] = new Word(STD, 0, -1, 10);
    aux[4] = new Word(STD, 0, -1, 11);
    aux[5] = new Word(STD, 0, -1, 12);
    aux[6] = new Word(STOP, -1, -1, -1);
    aux[7] = new Word(DATA, -1, -1, -1);
    aux[8] = new Word(DATA, -1, -1, -1);
    aux[9] = new Word(DATA, -1, -1, -1);
    aux[10] = new Word(DATA, -1, -1, -1);
    aux[11] = new Word(DATA, -1, -1, -1);
    aux[12] = new Word(DATA, -1, -1, -1);
    aux[13] = new Word(DATA, -1, -1, -1);
    progs[2] = new Program(14, "progMinimo", aux); //programa 3

    aux = (Word**)malloc(30*sizeof(Word*));
    aux[0] = new Word(LDI, 1, -1, 0);
    aux[1] = new Word(STD, 1, -1, 20);
    aux[2] = new Word(LDI, 2, -1, 1);
    aux[3] = new Word(STD, 2, -1, 21);
    aux[4] = new Word(LDI, 0, -1, 22);
    aux[5] = new Word(LDI, 6, -1, 6);
    aux[6] = new Word(LDI, 7, -1, 31);
    aux[7] = new Word(LDI, 3, -1, 0);
    aux[8] = new Word(ADD, 3, 1, -1);
    aux[9] = new Word(LDI, 1, -1, 0);
    aux[10] = new Word(ADD, 1, 2, -1);
    aux[11] = new Word(ADD, 2, 3, -1);
    aux[12] = new Word(STX, 0, 2, -1);
    aux[13] = new Word(ADDI, 0, -1, 1);
    aux[14] = new Word(SUB, 7, 0, -1);
    aux[15] = new Word(JMPIG, 6, 7, -1);
    aux[16] = new Word(STOP, -1, -1, -1);
    aux[17] = new Word(DATA, -1, -1, -1);
    aux[18] = new Word(DATA, -1, -1, -1);
    aux[19] = new Word(DATA, -1, -1, -1);
    aux[20] = new Word(DATA, -1, -1, -1);
    aux[21] = new Word(DATA, -1, -1, -1);
    aux[22] = new Word(DATA, -1, -1, -1);
    aux[23] = new Word(DATA, -1, -1, -1);
    aux[24] = new Word(DATA, -1, -1, -1);
    aux[25] = new Word(DATA, -1, -1, -1);
    aux[26] = new Word(DATA, -1, -1, -1);
    aux[27] = new Word(DATA, -1, -1, -1);
    aux[28] = new Word(DATA, -1, -1, -1);
    aux[29] = new Word(DATA, -1, -1, -1);
    progs[3] = new Program(30, "fibonacci10", aux); //programa 4

    aux = (Word**)malloc(32*sizeof(Word*));
    aux[0] = new Word(LDI, 1, -1, 0);
    aux[1] = new Word(STD, 1, -1, 20);
    aux[2] = new Word(LDI, 2, -1, 1);
    aux[3] = new Word(STD, 2, -1, 21);
    aux[4] = new Word(LDI, 0, -1, 22);
    aux[5] = new Word(LDI, 6, -1, 6);
    aux[6] = new Word(LDI, 7, -1, 31);
    aux[7] = new Word(MOVE, 3, 1, -1);
    aux[8] = new Word(MOVE, 1, 2, -1);
    aux[9] = new Word(ADD, 2, 3, -1);
    aux[10] = new Word(STX, 0, 2, -1);
    aux[11] = new Word(ADDI, 0, -1, 1);
    aux[12] = new Word(SUB, 7, 0, -1);
    aux[13] = new Word(JMPIG, 6, 7, -1);
    aux[14] = new Word(STOP, -1, -1, -1);
    aux[15] = new Word(DATA, -1, -1, -1);
    aux[16] = new Word(DATA, -1, -1, -1);
    aux[17] = new Word(DATA, -1, -1, -1);
    aux[18] = new Word(DATA, -1, -1, -1);
    aux[19] = new Word(DATA, -1, -1, -1);
    aux[20] = new Word(DATA, -1, -1, -1);
    aux[21] = new Word(DATA, -1, -1, -1);
    aux[22] = new Word(DATA, -1, -1, -1);
    aux[23] = new Word(DATA, -1, -1, -1);
    aux[24] = new Word(DATA, -1, -1, -1);
    aux[25] = new Word(DATA, -1, -1, -1);
    aux[26] = new Word(DATA, -1, -1, -1);
    aux[27] = new Word(DATA, -1, -1, -1);
    aux[28] = new Word(DATA, -1, -1, -1);
    aux[29] = new Word(DATA, -1, -1, -1);
    aux[30] = new Word(DATA, -1, -1, -1);
    aux[31] = new Word(DATA, -1, -1, -1);
    progs[4] = new Program(32, "fibonacci10v2", aux); //programa 5

    aux = (Word**)malloc(57*sizeof(Word*));
    aux[0] = new Word(LDI, 8, -1, 1);
	aux[1] = new Word(LDI, 9, -1, 55);
	aux[2] = new Word(SYSCALL, -1, -1, -1);
	aux[3] = new Word(LDD, 7, -1, 55);
	aux[4] = new Word(LDI, 3, -1, 0);
	aux[5] = new Word(ADD, 3, 7, -1);
	aux[6] = new Word(LDI, 4, -1, 36);
	aux[7] = new Word(LDI, 1, -1, -1);
	aux[8] = new Word(STD, 1, -1, 41);
	aux[9] = new Word(JMPIL, 4, 7, -1);
	aux[10] = new Word(JMPIE, 4, 7, -1);
	aux[11] = new Word(ADDI, 7, -1, 41);
	aux[12] = new Word(LDI, 1, -1, 0);
	aux[13] = new Word(STD, 1, -1, 41);
	aux[14] = new Word(SUBI, 3, -1, 1);
	aux[15] = new Word(JMPIE, 4, 3, -1);
	aux[16] = new Word(ADDI, 3, -1, 1);
	aux[17] = new Word(LDI, 2, -1, 1);
	aux[18] = new Word(STD, 2, -1, 42);
	aux[19] = new Word(SUBI, 3, -1, 2);
	aux[20] = new Word(JMPIE, 4, 3, -1);
	aux[21] = new Word(LDI, 0, -1, 43);
	aux[22] = new Word(LDI, 6, -1, 25);
	aux[23] = new Word(LDI, 5, -1, 0);
	aux[24] = new Word(ADD, 5, 7, -1);
	aux[25] = new Word(LDI, 7, -1, 0);
	aux[26] = new Word(ADD, 7, 5, -1);
	aux[27] = new Word(LDI, 3, -1, 0);
	aux[28] = new Word(ADD, 3, 1, -1);
	aux[29] = new Word(LDI, 1, -1, 0);
	aux[30] = new Word(ADD, 1, 2, -1);
	aux[31] = new Word(ADD, 2, 3, -1);
	aux[32] = new Word(STX, 0, 2, -1);
	aux[33] = new Word(ADDI, 0, -1, 1);
	aux[34] = new Word(SUB, 7, 0, -1);
	aux[35] = new Word(JMPIG, 6, 7, -1);
	aux[36] = new Word(STOP, -1, -1, -1);
	aux[37] = new Word(DATA, -1, -1, -1);
	aux[38] = new Word(DATA, -1, -1, -1);
	aux[39] = new Word(DATA, -1, -1, -1);
	aux[40] = new Word(DATA, -1, -1, -1);
	aux[41] = new Word(DATA, -1, -1, -1);
	aux[42] = new Word(DATA, -1, -1, -1);
	aux[43] = new Word(DATA, -1, -1, -1);
	aux[44] = new Word(DATA, -1, -1, -1);
	aux[45] = new Word(DATA, -1, -1, -1);
	aux[46] = new Word(DATA, -1, -1, -1);
	aux[47] = new Word(DATA, -1, -1, -1);
	aux[48] = new Word(DATA, -1, -1, -1);
	aux[49] = new Word(DATA, -1, -1, -1);
	aux[50] = new Word(DATA, -1, -1, -1);
	aux[51] = new Word(DATA, -1, -1, -1);
	aux[52] = new Word(DATA, -1, -1, -1);
	aux[53] = new Word(DATA, -1, -1, -1);
	aux[54] = new Word(DATA, -1, -1, -1);
	aux[55] = new Word(DATA, -1, -1, -1);
	aux[56] = new Word(DATA, -1, -1, -1);
    progs[5] = new Program(57, "fibonacciREAD", aux); //programa 6

    aux = (Word**)malloc(16*sizeof(Word*));
    aux[0] = new Word(LDI, 0, -1, 7);
	aux[1] = new Word(STD, 0, -1, 50);
	aux[2] = new Word(LDD, 0, -1, 50);
	aux[3] = new Word(LDI, 1, -1, -1);
	aux[4] = new Word(LDI, 2, -1, 13);
	aux[5] = new Word(JMPIL, 2, 0, -1);
	aux[6] = new Word(LDI, 1, -1, 1);
	aux[7] = new Word(LDI, 6, -1, 1);
	aux[8] = new Word(LDI, 7, -1, 13);
	aux[9] = new Word(JMPIE, 7, 0, 0);
	aux[10] = new Word(MULT, 1, 0, -1);
	aux[11] = new Word(SUB, 0, 6, -1);
	aux[12] = new Word(JMP, -1, -1, 9);
	aux[13] = new Word(STD, 1, -1, 15);
	aux[14] = new Word(STOP, -1, -1, -1);
	aux[15] = new Word(DATA, -1, -1, -1);
    progs[6] = new Program(16, "PB", aux);
    aux = (Word**)malloc(54*sizeof(Word*)); //programa 7

    aux[0] = new Word(LDI, 7, -1, 5);
	aux[1] = new Word(LDI, 6, -1, 5);
	aux[2] = new Word(LDI, 5, -1, 46);
	aux[3] = new Word(LDI, 4, -1, 47);
	aux[4] = new Word(LDI, 0, -1, 4);
	aux[5] = new Word(STD, 0, -1, 46);
	aux[6] = new Word(LDI, 0, -1, 3);
	aux[7] = new Word(STD, 0, -1, 47);
	aux[8] = new Word(LDI, 0, -1, 5);
	aux[9] = new Word(STD, 0, -1, 48);
	aux[10] = new Word(LDI, 0, -1, 1);
	aux[11] = new Word(STD, 0, -1, 49);
	aux[12] = new Word(LDI, 0, -1, 2);
	aux[13] = new Word(STD, 0, -1, 50);
	aux[14] = new Word(LDI, 3, -1, 25);
	aux[15] = new Word(STD, 3, -1, 99);
	aux[16] = new Word(LDI, 3, -1, 22);
	aux[17] = new Word(STD, 3, -1, 98);
	aux[18] = new Word(LDI, 3, -1, 38);
	aux[19] = new Word(STD, 3, -1, 97);
	aux[20] = new Word(LDI, 3, -1, 25);
	aux[21] = new Word(STD, 3, -1, 96);
	aux[22] = new Word(LDI, 6, -1, 0);
	aux[23] = new Word(ADD, 6, 7, -1);
	aux[24] = new Word(SUBI, 6, -1, 1);
	aux[25] = new Word(JMPIEM, -1, 6, 97);
	aux[26] = new Word(LDX, 0, 5, -1);
	aux[27] = new Word(LDX, 1, 4, -1);
	aux[28] = new Word(LDI, 2, -1, 0);
	aux[29] = new Word(ADD, 2, 0, -1);
	aux[30] = new Word(SUB, 2, 1, -1);
	aux[31] = new Word(ADDI, 4, -1, 1);
	aux[32] = new Word(SUBI, 6, -1, 1);
	aux[33] = new Word(JMPILM, -1, 2, 99);
	aux[34] = new Word(STX, 5, 1, -1);
	aux[35] = new Word(SUBI, 4, -1, 1);
	aux[36] = new Word(STX, 4, 0, -1);
	aux[37] = new Word(ADDI, 4, -1, 1);
	aux[38] = new Word(JMPIGM, -1, 6, 99);
	aux[39] = new Word(ADDI, 5, -1, 1);
	aux[40] = new Word(SUBI, 7, -1, 1);
	aux[41] = new Word(LDI, 4, -1, 0);
	aux[42] = new Word(ADD, 4, 5, -1);
	aux[43] = new Word(ADDI, 4, -1, 1);
	aux[44] = new Word(JMPIGM, -1, 7, 98);
	aux[45] = new Word(STOP, -1, -1, -1);
	aux[46] = new Word(DATA, -1, -1, -1);
	aux[47] = new Word(DATA, -1, -1, -1);
	aux[48] = new Word(DATA, -1, -1, -1);
	aux[49] = new Word(DATA, -1, -1, -1);
	aux[50] = new Word(DATA, -1, -1, -1);
	aux[51] = new Word(DATA, -1, -1, -1);
	aux[52] = new Word(DATA, -1, -1, -1);
	aux[53] = new Word(DATA, -1, -1, -1);
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
