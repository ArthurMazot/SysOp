#pragma once
#include <iostream>
#include "memory.hpp"
#include "enum.hpp"

using namespace std;

struct Program{
    public:
    int size;
    string name;
    Word **image;
    Program(int, string, Word**);
    ~Program();
};

struct Programs{
    public:
    int size;
    Program **progs;
    Programs();
    ~Programs();
    Program *retrieveProgram(string);
};