#include "IO.hpp"


std::queue<IO>               ioQueue;
std::mutex                   ioMutex;
std::condition_variable      ioCv;
