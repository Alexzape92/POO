#ifndef TARJETA_HPP_
#define TARJETA_HPP_
#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include "../P1/fecha.hpp"
#include <set>
#include <iostream>

class Usuario;

class Numero{
public:
    typedef enum{LONGITUD, DIGITOS, NO_VALIDO} Razon;
    class Incorrecto;

    explicit Numero(const Cadena& cad);
    operator const char*() const;
private:
    Cadena num;
};

 //Comparación
bool operator <(const Numero& n1, const Numero& n2);

class Numero::Incorrecto{
public:
    Incorrecto(Razon mot);
    Razon razon() const;
private:
    Razon motivo;
};

//Definiciones en línea de Numero y Numero::Incorrecto
inline Numero::operator const char *() const{
    return num.c_str();
}


inline Numero::Incorrecto::Incorrecto(Numero::Razon mot): motivo{mot}{}

inline Numero::Razon Numero::Incorrecto::razon() const{
    return motivo;
}

//-------------------------------------------------------------------------------------------
class Tarjeta{
public:
    typedef enum{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress} Tipo;
    class Caducada;
    class Num_duplicado;
    class Desactivada{};
    friend class Usuario;

    Tarjeta(const Numero& n, Usuario& tit, const Fecha& fec);

    //Métodos por defecto eliminados
    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator =(const Tarjeta&) = delete;

    //Observadores
    const Numero& numero() const;
    const Usuario* titular() const;
    const Fecha& caducidad() const;
    bool activa() const;
    Tipo tipo() const;

    //Modificadores
    bool activa(bool a);

    //Destructor
    ~Tarjeta();
private:
    const Numero num;
    const Usuario* titu;
    const Fecha caduc;
    bool act;

    void anula_titular();   //Para que solo la pueda llamar Usuario
    static std::set<Numero> numeros;
};

//Operadores de insercion en flujo
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& t);
std::ostream& operator <<(std::ostream& os, const Tarjeta& tj);

//Comparacion
bool operator <(const Tarjeta& tj1, const Tarjeta& tj2);


class Tarjeta::Caducada{
public:
    Caducada(const Fecha& cad);
    const Fecha& cuando() const;
private:
    Fecha caducidad;
};

class Tarjeta::Num_duplicado{
public:
    Num_duplicado(const Numero& n);
    const Numero& que() const;
private:
    Numero num;
};

//Definiciones en línea de Tarjeta::Caducada, Tarjeta::Num_duplicado y Tarjeta
inline Tarjeta::Caducada::Caducada(const Fecha& cad): caducidad{cad}{}

inline const Fecha& Tarjeta::Caducada::cuando() const{
    return caducidad;
}

inline Tarjeta::Num_duplicado::Num_duplicado(const Numero& n): num{n}{}

inline const Numero& Tarjeta::Num_duplicado::que() const{
    return num;
}

inline const Numero& Tarjeta::numero() const{
    return num;
}

inline const Usuario* Tarjeta::titular() const{
    return titu;
}

inline const Fecha& Tarjeta::caducidad() const{
    return caduc;
}

inline bool Tarjeta::activa() const{
    return act;
}

inline void Tarjeta::anula_titular(){
    titu = nullptr;
    act = false;
}

inline bool Tarjeta::activa(bool a){
    return act = a;
}

#endif
