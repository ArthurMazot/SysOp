#pragma once

enum Opcode : int{
    ___, DATA,
    JMP, JMPI, JMPIG, JMPIL, JMPIE,
    JMPIM, JMPIGM, JMPILM, JMPIEM,
    JMPIGK, JMPILK, JMPIEK, JMPIGT,
    ADDI, SUBI, ADD, SUB, MULT,
    LDI, LDD, STD, LDX, STX, MOVE,
    SYSCALL, STOP};

enum Interrupts : int{
    noInterrupt, intEnderecoInvalido, intInstrucaoInvalida, intOverflow
};