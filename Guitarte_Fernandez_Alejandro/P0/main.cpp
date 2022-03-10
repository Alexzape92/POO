#include "Fecha.hpp"
#include <iostream>

int main(){
    Fecha f("000/00/00002021");
    std::cout << f.dia() << '/' << f.mes() << '/' << f.anno() << std::endl;

    return 0;
}