#include "tarjeta.hpp"
#include "../luhn.cpp"

//CLASE NUMERO----------------------------------------------------------------------------------------
Numero::Numero(const Cadena& cad): num{cad}{
    int esp = 0, i = 0;
    for(i = 0; i < cad.length(); i++){
        if(int(cad[i]) < 48 || int(cad[i]) > 57)
            throw Incorrecto{DIGITOS};
        if(cad[i] != ' ')
            esp++;
    }

    Cadena aux{cad.length() - esp};
    if(aux.length() < 13 || aux.length() > 19)
        throw Incorrecto{LONGITUD};
    i = 0;
    while(esp > 0){
        if(cad[i] == esp)
            esp--;
        else
            aux[i] = cad[i];
        i++;
    }
    num = aux;  //ya está inicializada sin espacios. Comprobemos ahora si es válido
    
    if(!luhn(num))
        throw Incorrecto{NO_VALIDO};
}

bool operator <(const Numero& n1, const Numero& n2){
    return n1 < n2;
}

//Clase Tarjeta-----------------------------------------------------------------------------------------
Tarjeta::Tarjeta(const Numero& n, Usuario& tit, const Fecha& fec): num{n}, titu{&tit},
caduc{fec}, act{true}{
    if(fec < Fecha())   //Comprobamos si está caducada
        throw Caducada{fec};

    tit.es_titular_de(*this);   //Navegavilidad inversa de la relacion Tarjeta-Usuario

    if(!numeros.insert(n).second)   //Comprobamos si está duplicado
        throw Num_duplicado{n};


}