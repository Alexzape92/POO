#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iostream>

class Articulo{
public:
    //Constructor
    Articulo(const Cadena& c, const Cadena& t, const Fecha& fec, double pr, int ex = 0);

    //Observadores y modificadores
    const Cadena& referencia() const;
    const Cadena& titulo() const;
    const Fecha& f_publi() const;
    double precio() const;
    double& precio();
    int stock() const;
    int& stock();
private:
    const Cadena cod, tit;
    const Fecha pub;
    double prec;
    int exist;
};

//Inserción en flujo de salida
std::ostream& operator <<(std::ostream& os, const Articulo& art);


//Implementaciones en línea
inline Articulo::Articulo(const Cadena& c, const Cadena& t, const Fecha& fec, double pr, int ex): cod{c}, tit{t}, pub{fec}, prec{pr}, exist{ex}{}

inline const Cadena& Articulo::referencia() const{
    return cod;
}

inline const Cadena& Articulo::titulo() const{
    return tit;
}

inline const Fecha& Articulo::f_publi() const{
    return pub;
}

inline double Articulo::precio() const{
    return prec;
}

inline double& Articulo::precio(){
    return prec;
}

inline int Articulo::stock() const{
    return exist;
}

inline int& Articulo::stock(){
    return exist;
}

#endif