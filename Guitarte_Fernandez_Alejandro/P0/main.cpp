#include "Fecha.hpp"
#include <iostream>

int main(){
    Fecha f(20, 3);

    f = f - 50;
    std::cout << f.dia() << '/' << f.mes() << '/' << f.anno() << std::endl;

    return 0;
}