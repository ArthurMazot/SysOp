#ifndef GM_H
#define GM_H

#include <vector>

using namespace std;

class GM{
private:
    int tamPag;
    vector<bool> pags;
public:
    GM(int tamM, int tamp);
    bool aloca(int numPalavras, vector<int>& tabPag);
    void desaloca(vector<int>& tabPag);
};

#endif