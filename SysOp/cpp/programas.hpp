#pragma once
#include <iostream>
#include "memory.hpp"
using namespace std;

struct Program{
    int size;
    string name;
    Word **image;
    Program(int, string, Word**);
    ~Program();
};

struct Programs{
    int size;
    Program **progs;
    Programs();
    ~Programs();
    Word **retrieveProgram(string);
};