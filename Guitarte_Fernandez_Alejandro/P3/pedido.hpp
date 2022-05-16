#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "usuario_pedido.hpp"

class Pedido_Articulo;

class Pedido{
public:
    //Constructores
    Pedido(Usuario_Pedido& up, Pedido_Articulo& pa,const Usuario& us, const Tarjeta& tarj, Fecha fec = Fecha());   

    //Observadores
    int numero() const {return num;}
    const Fecha& fecha() const {return fch;}
    const Tarjeta& tarjeta() const {return *tj;}
    double total() const {return imp;}
private:
    int num;
    const Tarjeta* tj;
    Fecha fch;
    double imp;

    //Para el contador del numero
    static int ultimo;
};




#endif