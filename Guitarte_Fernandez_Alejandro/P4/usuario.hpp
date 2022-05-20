#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include "../P1/cadena.hpp"

#include "tarjeta.hpp"
#include "articulo.hpp"
#include <iostream>
#include <unordered_set>
#include <map>
#include <unordered_map>

class Numero;
class Tarjeta;

class Clave{
public:
    typedef enum{CORTA, ERROR_CRYPT} Razon;
    class Incorrecta;

    //Constructor
    Clave(const char* passwd);

    //Observadores
    Cadena clave() const;
    bool verifica(const char* passwd) const;
private:
    Cadena pass;
};

//Definiciones en línea Clave
inline Cadena Clave::clave() const{
    return pass;
}

class Clave::Incorrecta{
public:
    Incorrecta(Razon r);
    Razon razon() const;
private:
    Razon why;
};

//Definiciones en línea Clave::Incorrecta
inline Clave::Incorrecta::Incorrecta(Razon r): why{r}{}

inline Clave::Razon Clave::Incorrecta::razon() const{
    return why;
}

//USUARIO------------------------------------------------------------------------------------------------------------------

class Usuario{
public:
    //Relaciones
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    void es_titular_de(const Tarjeta& tj);
    void no_es_titular_de(Tarjeta& tj);
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    //Excepciones
    class Id_duplicado;

    //Constructor
    Usuario(const Cadena& ident, const Cadena& nomb, const Cadena& apell, const Cadena& direc, const Clave& cl);
    Usuario(const Usuario&) = delete;
    Usuario& operator =(const Usuario&) = delete;

    //Observadores
    const Cadena& id() const;
    const Cadena& nombre() const;
    const Cadena& apellidos() const;
    const Cadena& direccion() const;
    const Tarjetas& tarjetas() const;
    const Articulos& compra() const;
    unsigned int n_articulos() const;

    //Modificadores
    void compra(Articulo& art, unsigned int cant = 1);

    //Destructor
    ~Usuario();

    //operador de insercion en flujo de salida
    friend std::ostream& operator <<(std::ostream& os, const Usuario& us);
private:
    const Cadena ide, nom, ape, dir;
    Clave pass;
    Tarjetas tarjs;
    Articulos carrito;

    //Repetidos
    static std::unordered_set<Cadena> registrados;
};

//Carro
void mostrar_carro(std::ostream& os, const Usuario& us);

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

inline unsigned int Usuario::n_articulos() const{
    return carrito.size();
}



class Usuario::Id_duplicado{
public:
    Id_duplicado(const Cadena& idup);
    const Cadena& idd() const;
private:
    Cadena idupli;
};

//Definiciones en línea-------------------------------------------------------------------------------------
inline Usuario::Id_duplicado::Id_duplicado(const Cadena& idup): idupli{idup}{}

inline const Cadena& Usuario::Id_duplicado::idd() const{
    return idupli;
}

#endif
