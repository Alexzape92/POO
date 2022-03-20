CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -g
CPPFLAGS=-DP0 -I../Tests-auto -I.
VPATH=../Tests-auto:.


all: test-P0-auto

test-P0-auto: test-caso0-fecha-auto.o test-auto.o fecha.o
	$(CXX) -o $@ $^

test-caso0-fecha-auto.o test-auto.o: test-auto.hpp fecha.hpp 

fecha.o: fecha.cpp fecha.hpp
	$(CXX) -c $(CXXFLAGS) fecha.cpp

clean:
	rm -rf test-P0-auto *.o core *~
	rm -rf Prueba

Prueba: main.o Fecha.o
	$(CXX) -o Prueba main.o Fecha.o

main.o: main.cpp Fecha.hpp
	$(CXX) -c $(CXXFLAGS) main.cpp