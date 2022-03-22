#include "cadena.hpp"
#include <cstring>
#include <iostream>

int main(){
    Cadena str{"eenie meenie moe"};

    std::cout << str.substr(6, 6) << std::endl;

    return 0;
}