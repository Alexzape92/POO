#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "usuario_pedido.hpp"

class Pedido_Articulo;

class Pedido{
public:
    Pedido(Usuario_Pedido& up, Pedido_Articulo& pa,const Usuario& us, const Tarjeta& tarj, Fecha fec = Fecha());   
private:
    int num;
    const Tarjeta* tj;
    Fecha fch;
    int imp;

    //Para el contador del numero
    static int ultimo;
};




#endif