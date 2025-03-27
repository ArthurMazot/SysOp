#pragma once
#include "cpu.hpp"
#include "programas.hpp"
#include "memory.hpp"

CPU::CPU(Memory *_mem, bool _debug){
    maxInt = 32767;
    minInt = -32767;
    mem = _mem;
    debug = _debug;}

CPU::~CPU(){
    delete mem;}