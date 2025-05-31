#pragma once

#include <queue>
#include <mutex>

#include <condition_variable>

//using namespace std;
extern std::queue<IO>            ioQueue;
extern std::mutex                ioMutex;
extern std::condition_variable   ioCv;

enum ioType {
    READ,
    WRITE
}type;

//pedido de I/O 
typedef struct IO{
    int pid; // id do proc q faz a requisição
    ioType type;
    int address; // endereco de memoria
    int valueType; // type == write
}IO;


