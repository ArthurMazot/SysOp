CFLAGS =-c -std=c++11
EXEC = app

all: ${EXEC}

${EXEC}: memory.o programas.o GMGP.o cpu.o hwso.o sistema.o main.o
	@g++ -o ${EXEC} main.o sistema.o hwso.o cpu.o GMGP.o programas.o memory.o

main.o: main.cpp enum.hpp memory.hpp programas.hpp cpu.hpp hwso.hpp sistema.hpp
	@g++ ${CFLAGS} main.cpp

sistema.o: sistema.cpp enum.hpp memory.hpp programas.hpp cpu.hpp hwso.hpp sistema.hpp
	@g++ ${CFLAGS} sistema.cpp

hwso.o: hwso.cpp enum.hpp memory.hpp programas.hpp cpu.hpp hwso.hpp
	@g++ ${CFLAGS} hwso.cpp

cpu.o: cpu.cpp enum.hpp memory.hpp programas.hpp cpu.hpp hwso.hpp
	@g++ ${CFLAGS} cpu.cpp

GMGP.o: GMGP.cpp GMGP.hpp programas.hpp memory.hpp
	@g++ ${CFLAGS} GMGP.cpp

programas.o: programas.cpp enum.hpp memory.hpp programas.hpp
	@g++ ${CFLAGS} programas.cpp

memory.o: memory.cpp enum.hpp memory.hpp
	@g++ ${CFLAGS} memory.cpp

run: ${EXEC}
	@./${EXEC}

cleanl:
	@rm ${EXEC} -f main.o sistema.o hwso.o cpu.o GMGP.o programas.o memory.o

cleanw:
	@del ${EXEC} main.o sistema.o hwso.o cpu.o GMGP.o programas.o memory.o