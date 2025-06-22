#pragma once
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "hwso.hpp"
#include "GMGP.hpp"
#include "enum.hpp"
#include "cpu.hpp"
#include "sistema.hpp"

extern Sistema* sistema;

using namespace std;

struct IO{
    int pid;
    IOType tipo;
    int address;
};

class IOGerenciamento{
    public:
        queue<PCB*> filaBloqueados;
        queue<IO> filaRequisicoes;
        mutex IOMutex;
        condition_variable cvInterrupcaoFinalizada;
        condition_variable cvNewRequesicao;
        IO reqAtual;
        bool reqPendente = false;

        /* Função para add uma nova requisição I/O */
        void adicionaReq(PCB* pcb, IOType tipo, int address);
        void threadIO();
        void valorDeEntrada(int pid, int valor);
        void InterrupcaoFinalizada();
        void gerarInterrupcao();
};