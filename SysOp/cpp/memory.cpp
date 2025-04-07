#pragma once
#include <iostream>
#include "memory.hpp"
#include "enum.hpp"

using namespace std;

Word::Word(Opcode _opc, int _ra, int _rb, int _p){
	opc = _opc;
	ra = _ra;
	rb = _rb;
	p  = _p;}

Word::~Word(){}

void Word::setWord(Opcode _opc, int _ra, int _rb, int _p){
    opc = _opc;
	ra = _ra;
	rb = _rb;
	p  = _p;}

void Word::operator=(Word &w){
    setWord(w.opc, w.ra, rb = w.rb, w.p);}

//===================================//

Memory::Memory(int s){
    size = s;
    pos = (Word*)malloc(size*sizeof(Word));}
    
Memory::~Memory(){
    delete pos;}