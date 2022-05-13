CXX=clang++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic -g
CPPFLAGS=-DP1 -I../Tests-auto -I.
VPATH=../Tests-auto:.
RM = rm

MIS_OBJ = fecha.o cadena.o
AUTO_OBJ = test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o
MIS_HDR = fecha.hpp cadena.hpp
AUTO_HDR = test-auto.hpp
AUTO_EXE = test-P0-auto
CONS_EXE = test-fechacadena-consola
CONS_OBJ = test-fechacadena-consola.o

#VALGRIND(DEPENDE DE AUTO Y CONSOLA)
#FECHA YA PASA LOS TESTS-AUTO

all: $(AUTO_EXE) $(CONS_EXE)

$(AUTO_EXE): $(AUTO_OBJ) $(MIS_OBJ)
	$(CXX) -o $@ $^

$(AUTO_OBJ): $(AUTO_HDR) $(MIS_HDR)

$(CONS_EXE): $(CONS_OBJ) $(MIS_OBJ)
	$(CXX) -o $@ $^

$(CONS_OBJ): $(MIS_HDR)

check:
	make -f Make_check.mk $@

cadena.o: cadena.hpp

fecha.o: fecha.hpp

valgrind: $(AUTO_EXE) $(CONS_EXE)
	valgrind ./$<
	valgrind ./test-fechacadena-consola

clean:
	$(RM) -rf test-P0-auto test-fechacadena-consola *.o core *~
