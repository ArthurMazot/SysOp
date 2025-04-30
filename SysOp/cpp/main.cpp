#pragma once
#include <iostream>
#include <thread>
#include "enum.hpp"
#include "memory.hpp"
#include "programas.hpp"
#include "cpu.hpp"
#include "hwso.hpp"
#include "sistema.hpp"

using namespace std;

char flag = 1;

void run(Sistema *s){
    s->hw->cpu->run();}

void interface(Sistema *s){
    string buff;
    while(1){
    cout << "-> "; 
    cin >> buff;

    if(buff == "new"){
        cin >> buff;
        s->NEW(buff);}

    else if(buff == "rm"){
        cin >> buff;
        if(buff[0] >= '0' && buff[0] <= '9') s->rm(stoi(buff));}

    else if(buff == "dump"){
        cin >> buff;
        if(buff[0] >= '0' && buff[0] <= '9') s->dump(stoi(buff));}

    else if(buff == "exec"){
        cin >> buff;
        if(buff == "all") s->execAll();
        else if(buff[0] >= '0' && buff[0] <= '9') s->exec(stoi(buff));}

    else if(buff == "ps") s->ps();
    else if(buff == "dumpM") s->dumpM(0, s->tamMem);
    else if(buff == "traceOn") s->traceOn();
    else if(buff == "traceOff") s->traceOff();
    else if(buff == "clear") system("clear");
    else if(buff == "exit"){ 
        flag = 0;
        break;}
    else cout << "Opção inválida" << endl;}}

int main(){
    system("clear");
    Sistema *s = new Sistema(8, 1024); //tamPag, tamMem
    thread p1 (interface, s);
    thread p2 (run, s);
  
    p1.join();
    p2.join();}