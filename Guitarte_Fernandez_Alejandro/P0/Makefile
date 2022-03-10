CXX = g++
CXXFLAGS = -std=c++17


all: Prueba

Prueba: main.o Fecha.o
	$(CXX) -o Prueba main.o Fecha.o

main.o: main.cpp Fecha.hpp
	$(CXX) -c $(CXXFLAGS) main.cpp 

Fecha.o: Fecha.cpp Fecha.hpp
	$(CXX) -c $(CXXFLAGS) Fecha.cpp

clean:
	rm -rf Prueba Fecha.o main.o core *~
