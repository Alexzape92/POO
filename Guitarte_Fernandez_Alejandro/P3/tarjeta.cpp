#include "tarjeta.hpp"
#include "usuario.hpp"
#include <cstring>
#include <functional>
#include <iterator>

//Para luhn
bool luhn(const Cadena&);

std::set<Numero> Tarjeta::numeros{};

//CLASE NUMERO----------------------------------------------------------------------------------------
Numero::Numero(const Cadena& cad){
    Cadena aux{cad};
    auto fin = std::remove_if(aux.begin(), aux.end(), EsBlanco{});

    if(fin != aux.end()){
        *fin = '\0';
        Cadena sd (aux.c_str());
        aux = sd;
    }
    if(std::find_if(aux.begin(), aux.end(), std::not1(EsDigito{})) != aux.end())
        throw Incorrecto{DIGITOS};

    if(aux.length() < 13 || aux.length() > 19)
        throw Incorrecto{LONGITUD};
    
    if(!luhn(aux))
        throw Incorrecto{NO_VALIDO};
    
    num = aux;
}

bool operator <(const Numero& n1, const Numero& n2){
    return strcmp(n1, n2) < 0;
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

Tarjeta::Tipo Tarjeta::tipo() const{
    switch(num[0]){
        case '3': if(num[1] == '4' || num[1] == '7') return Tipo{AmericanExpress}; else return Tipo{JCB}; break;
        case '4': return Tipo{VISA}; break;
        case '5': return Tipo{Mastercard}; break;
        case '6': return Tipo{Maestro}; break;
        default: return Tipo{Otro}; break;
    }
}

Tarjeta::~Tarjeta(){
    if(titu != nullptr)
        const_cast<Usuario*>(titu)->no_es_titular_de(*this);
    
    numeros.erase(this->num);
}

//Operador de insercion en flujo de salida
//Operadores de insercion en flujo
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& t){
    static Cadena cadenas[] {"Otro", "VISA", "Mastercard", "Maestro", "JCB", "American Express"};

    return os << cadenas[t];
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& tj){
    os << tj.tipo() << std::endl;
    os << tj.numero() << std::endl;

    Cadena nombre{tj.titular()->nombre().c_str()}, apellidos{tj.titular()->apellidos().c_str()};  //Guardamos las cadenas en cuestion
    for(auto i = nombre.begin(); i != nombre.end(); i++)
        *i = toupper((unsigned char) *i);
    for(auto i = apellidos.begin(); i != apellidos.end(); i++)
        *i = toupper((unsigned char) *i);

    os << nombre << " " << apellidos << std::endl;

    os << "Caduca: ";
    if(tj.caducidad().mes() < 10)
        os << "0" << tj.caducidad().mes();
    else
        os << tj.caducidad().mes();
    if(tj.caducidad().anno() % 1000 < 10)
        os << "/0" << tj.caducidad().anno() % 1000 << std::endl;
    else
        os << "/" << tj.caducidad().anno() % 1000 << std::endl;
    
    return os;
}

//Comparacion
bool operator <(const Tarjeta& tj1, const Tarjeta& tj2){
    return tj1.numero() < tj2.numero();
}
