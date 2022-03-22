CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic -g
CPPFLAGS=-DP0 -I../Tests-auto -I.
VPATH=../Tests-auto:.


all: test-P0-auto

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o cadena.o fecha.o
	$(CXX) -o $@ $^

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: test-auto.hpp fecha.hpp cadena.hpp

cadena.o: cadena.cpp cadena.hpp
	$(CXX) -c cadena.cpp

fecha.o: fecha.cpp fecha.hpp
	$(CXX) -c fecha.cpp

clean:
	rm -rf test-P0-auto *.o core *~
	rm -rf Prueba

Prueba: main.o cadena.o
	$(CXX) -o Prueba main.o cadena.o

main.o: main.cpp cadena.hpp
	$(CXX) -c main.cpp