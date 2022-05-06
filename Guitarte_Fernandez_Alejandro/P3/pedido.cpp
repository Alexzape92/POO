#include "pedido.hpp"

int Pedido::ultimo{1};  //El primer pedido será el 1


Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa,const Usuario& us, const Tarjeta& tarj, Fecha fec):
num{ultimo++}, tj{&tarj}, fch{fec}, imp{0}{
    up.asocia(*this, const_cast<Usuario&>(us));    //Relacion Usuario-Pedido
    //HACER AQUÍ RELACION PEDIDO-ARTÍCULO

    //Terminar
}