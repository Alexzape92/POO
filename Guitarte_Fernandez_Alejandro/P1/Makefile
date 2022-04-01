CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic -g
CPPFLAGS=-DP1 -I../Tests-auto -I.
VPATH=../Tests-auto:.
RM = rm

MIS_OBJ = cadena.o fecha.o
AUTO_OBJ = test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o
MIS_HDR = fecha.hpp cadena.hpp
AUTO_HDR = test-auto.hpp
AUTO_EXE = test-P0-auto

#AÑADIR REGLA CONSOLA, VALGRIND(DEPENDE DE AUTO Y CONSOLA), Y USAR MÁS MACROS

all: $(AUTO_EXE)

$(AUTO_EXE): $(AUTO_OBJ) $(MIS_OBJ)
	$(CXX) -o $@ $^

$(AUTO_OBJ): $(AUTO_HDR) $(MIS_HDR)

check:
	make -f Make_check.mk $@

cadena.o: cadena.hpp

fecha.o: fecha.hpp

prueba: main.o $(MIS_OBJ)
	$(CXX) -o $@ $^

main.o: fecha.hpp

clean:
	$(RM) -rf test-P0-auto prueba *.o core *~
