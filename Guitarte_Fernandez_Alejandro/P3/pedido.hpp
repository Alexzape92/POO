#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "usuario.hpp"
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include <iostream>

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido{
public:
    //Constructores
    Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& us, const Tarjeta& tarj, const Fecha& fec = Fecha());   

    //Observadores
    int numero() const {return num;}
    const Fecha& fecha() const {return fch;}
    const Tarjeta* tarjeta() const {return tarjeta_;}
    double total() const {return imp;}
    static int n_total_pedidos() {return ultimo;}

    //Excepciones
    class SinStock;
    class Vacio;
    class Impostor;
private:
    int num;
    const Tarjeta* tarjeta_;
    Fecha fch;
    double imp;

    //Para el contador del numero
    static int ultimo;
};

//Operador de inserción en flujo de salida
std::ostream& operator <<(std::ostream& os, const Pedido& ped);

//EXCEPCIONES---------------------------------------------------------------------------------------------------------------------------
class Pedido::SinStock{
    Articulo *art;
public:
    SinStock(Articulo* arti);
    Articulo& articulo() const;
};

inline Pedido::SinStock::SinStock(Articulo* arti): art{arti}{}

inline Articulo& Pedido::SinStock::articulo() const{
    return *art;
}


class Pedido::Vacio{
    Usuario *us;
public:
    Vacio(Usuario& user);
    const Usuario& usuario() const{return *us;}
};

inline Pedido::Vacio::Vacio(Usuario& user): us{&user}{}


class Pedido::Impostor{
    Usuario *us;
public:
    Impostor(Usuario& user);
    const Usuario& usuario() const{return *us;}
};

inline Pedido::Impostor::Impostor(Usuario& user): us{&user}{}



#endif