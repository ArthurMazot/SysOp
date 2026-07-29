## Sobre o Projeto

Este projeto é uma simulação completa de sistema operacional desenvolvida em C++ como projeto final da disciplina de Sistemas Operacionais. O projeto implementa em software os principais subsistemas de um SO real: CPU, gerência de memória (física e virtual), gerência de processos, escalonador, chamadas de sistema e terminal de interação com o usuário.
O objetivo foi compreender em profundidade o funcionamento interno de um sistema operacional por meio da implementação prática de seus componentes fundamentais.


## Funcionalidades Implementadas

- CPU simulada em software — execução de instruções e controle de fluxo
- Gerente de Processos — criação, controle e encerramento de processos
- Escalonador Round-robin — cada processo tem um tempo igual de uso e CPU
- Gerente de Memória — alocação e liberação de memória física
- Memória Virtual — implementada com paginação + segmentação
- Chamadas de Sistema (syscalls) — interface entre processos e o kernel simulado
- Terminal interativo — interface de linha de comando para comunicação com o usuário


## Arquivos

(main.cpp) -> Ponto de entrada e inicialização do sistema 
(cpu.cpp / cpu.hpp) -> Simulação da CPU e execução de instruções 
(memory.cpp / memory.hpp) -> Gerência de memória física e virtual 
(sistema.cpp / sistema.hpp) -> Núcleo do sistema operacional
(programas.cpp / programas.hpp) -> Representação e carregamento de processos/programas 
(GMGP.cpp / GMGP.hpp) -> Gerente de Memória e Gerente de Processos 
(hwso.cpp / hwso.hpp) -> Iterrupções de hardware e software 
(enum.hpp) -> Definições de enumerações e constantes do sistema 
(makefile) -> Script de compilação do projeto 


## Conceitos Aplicados

- Escalonamento de processos (Round-robin)
- Gerência de memória física
- Memória virtual com paginação e segmentação
- Chamadas de sistema (syscalls)
- Simulação de CPU em software
- Programação orientada a objetos em C++

## Colaboradores

- Arthur Mazot [https://github.com/ArthurMazot]
- Virgínia Muller [https://github.com/virginiasm]

Projeto desenvolvido como trabalho acadêmico da PUCRS — Curso de Engenharia de Computação.
