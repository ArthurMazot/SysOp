#pragma once
#include <iostream>
#include "memory.hpp"
using namespace std;

Word::Word(Opcode _opc, int _ra, int _rb, int _p){
	opc = _opc;
	ra = _ra;
	rb = _rb;
	p  = _p;}

Word::Word(){
    opc = ___;
    ra = -1;
	rb = -1;
	p  = -1;}

Word::~Word(){}

void Word::operator=(Word &w){
    opc = w.opc;
    ra = w.ra;
    rb = w.rb;
    p = w.p;}

//===================================//

Memory::Memory(int s){
    size = s;
    pos = (Word*)malloc(size*sizeof(Word));}
    
Memory::~Memory(){
    delete pos;}