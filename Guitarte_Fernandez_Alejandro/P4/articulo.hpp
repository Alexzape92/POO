#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iostream>
#include <set>

//AUTOR--------------------------------------------------------------------------------------------
class Autor{
    Cadena nombre_, apellidos_, direccion_;
public:
    Autor(const Cadena& nom, const Cadena& ape, const Cadena& dir): nombre_{nom}, apellidos_{ape}, direccion_{dir}{}
    const Cadena& nombre() const {return nombre_;}
    const Cadena& apellidos() const {return apellidos_;}
    const Cadena& direccion() const {return direccion_;}
};


//ARTICULO-----------------------------------------------------------------------------------------
class Articulo{
public:
    //Clase abstracta
    virtual void impresion_especifica(std::ostream& os) const = 0;

    //Relacion con autores
    typedef std::set<Autor*> Autores;

    //Constructor
    Articulo(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr);

    //Observadores y modificadores
    Autores autores() const;
    const Cadena& referencia() const;
    const Cadena& titulo() const;
    const Fecha& f_publi() const;
    double precio() const;
    double& precio();

    virtual void mostrar(std::ostream& os) = 0;

    virtual ~Articulo();
private:
    Autores aus;
    const Cadena cod, tit;
    const Fecha pub;
    double prec;
};

//Inserción en flujo de salida
std::ostream& operator <<(std::ostream& os, const Articulo& art);


//Implementaciones en línea
inline Articulo::Articulo(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr): aus{au}, cod{c}, tit{t}, pub{fec}, prec{pr}{}

inline Articulo::Autores Articulo::autores() const{
    return aus;
}

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

//LIBRODIGITAL-------------------------------------------------------------------------------------
class LibroDigital: public Articulo{
    Fecha exp;
public:
    LibroDigital(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr, const Fecha& ex):
    Articulo{au, c, t, fec, pr}, exp{ex}{}

    const Fecha& f_expir() const {return exp;}
};

//ARTICULOALMACENABLE(ABS)------------------------------------------------------------------------------
class ArticuloAlmacenable: public Articulo{
    int stock_;
public:
    ArticuloAlmacenable(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr, int st = 0):
    Articulo{au, c, t, fec, pr}, stock_{st}{}

    int stock() const {return stock_;}
    int& stock() {return stock_;}
};

//LIBRO-------------------------------------------------------------------------------------------------
class Libro: public ArticuloAlmacenable{
    
};

#endif