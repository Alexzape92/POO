#ifndef USUARIO_HPP_
#define USUARIO_HPP_
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <map>
#include <unordered_map>

class Clave{}; //Hacer más adelante

class Usuario{
public:
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    //Observadores
    const Cadena& id() const;
    const Cadena& nombre() const;
    const Cadena& apellidos() const;
    const Cadena& direccion() const;
    const Tarjetas& tarjetas() const;
    const Articulos& compra() const;
private:
    const Cadena ide, nom, ape, dir;
    Clave pass;
    Tarjetas tarjs;
    Articulos carrito;
};

//Implementaciones en línea
inline const Cadena& Usuario::id() const{
    return ide;
}

inline const Cadena& Usuario::nombre() const{
    return nom;
}

inline const Cadena& Usuario::apellidos() const{
    return ape;
}

inline const Cadena& Usuario::direccion() const{
    return dir;
}

inline const Usuario::Tarjetas& Usuario::tarjetas() const{
    return tarjs;
}

inline const Usuario::Articulos& Usuario::compra() const{
    return carrito;
}

#endif