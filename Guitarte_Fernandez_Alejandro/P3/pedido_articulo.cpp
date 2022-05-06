#include "pedido_articulo.hpp"
#include <iomanip>

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double prec, int cant){
    ped_art[&ped][&art] = LineaPedido(prec, cant);
    art_ped[&art][&ped] = LineaPedido(prec, cant);
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double prec, int cant){
    pedir(ped, art, prec, cant);
}



std::ostream& operator <<(std::ostream& os, const LineaPedido& lp){
    return os << std::fixed << std::setprecision(2) << lp.precio_venta()<< " €\t" << lp.cantidad() << std::endl;
}
