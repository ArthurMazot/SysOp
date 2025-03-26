#include "programas.cpp"

enum Interrupts : int{
    noInterrupt, intEnderecoInvalido, intInstrucaoInvalida, intOverflow
};

class CPU{
    int maxInt;
    int minInt;
    int pc;
    Word ir;
    int reg[10];
    Interrupts irpt;
    Memory *mem;

    //InterruptHandling ih;
    //SysCallHandling sysCall;

    bool cpuStop;
    bool debug;
    //Utilities u;

    CPU(Memory *_mem, bool _debug){
        maxInt = 32767;
        minInt = -32767;
        mem = _mem;
        debug = _debug;}

    ~CPU(){
        delete mem;}
};