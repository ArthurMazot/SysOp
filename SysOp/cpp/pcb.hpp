#ifndef PCB_H
#define PCB_H

#include <vector>

using namespace std;

class PCB{
    public: 
        int id;
        vector<int> tabPag;
        bool rodando;
        int pc;

        PCB(int i, vector<int>& tab);
};

#endif