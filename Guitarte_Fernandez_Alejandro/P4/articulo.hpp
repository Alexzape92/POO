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
    const Cadena& nombre() const noexcept {return nombre_;}
    const Cadena& apellidos() const noexcept {return apellidos_;}
    const Cadena& direccion() const noexcept {return direccion_;}
};


//ARTICULO-----------------------------------------------------------------------------------------
class Articulo{
public:
    //Clase abstracta
    virtual void impresion_especifica(std::ostream& os) const = 0;

    //Excepciones
    class Autores_vacios{};

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

    virtual ~Articulo(){}
private:
    Autores aus;
    const Cadena cod, tit;
    const Fecha pub;
    double prec;
};

//Inserción en flujo de salida
std::ostream& operator <<(std::ostream& os, const Articulo& art);


//Implementaciones en línea
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
    Fecha f_expir_;
public:
    LibroDigital(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr, const Fecha& ex):
    Articulo{au, c, t, fec, pr}, f_expir_{ex}{}

    const Fecha& f_expir() const {return f_expir_;}
    void impresion_especifica(std::ostream& os) const;
};

//ARTICULOALMACENABLE(ABS)------------------------------------------------------------------------------
class ArticuloAlmacenable: public Articulo{
protected:
    int stock_;
public:
    ArticuloAlmacenable(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr, int st = 0):
    Articulo{au, c, t, fec, pr}, stock_{st}{}

    int stock() const {return stock_;}
    int& stock() {return stock_;}
    virtual void impresion_especifica(std::ostream& os) const = 0;
};

//LIBRO-------------------------------------------------------------------------------------------------
class Libro: public ArticuloAlmacenable{
    int n_pag_;
public:
    Libro(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr, int npag, int st = 0):
    ArticuloAlmacenable{au, c, t, fec, pr, st}, n_pag_{npag}{}

    int n_pag() const{return n_pag_;}
    void impresion_especifica(std::ostream& os) const;
};

class Cederron: public ArticuloAlmacenable{
    int tam_;
public:
    Cederron(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr, int tam, int st = 0):
    ArticuloAlmacenable{au, c, t, fec, pr, st}, tam_{tam}{}

    int tam() const{return tam_;}
    void impresion_especifica(std::ostream& os) const;

};

#endif