#include "tarjeta.hpp"

int main(){
    try{
        Numero num{"4164 2959 2196 7832"};
    }catch(const Numero::Incorrecto& e){
        std::cout << e.razon();
    }

    return 0;
}