#include "pedido_articulo.hpp"
#include <iomanip>

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double prec, int cant){
    ped_art[&ped][&art] = LineaPedido(prec, cant);
    art_ped[&art][&ped] = LineaPedido(prec, cant);
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double prec, int cant){
    pedir(ped, art, prec, cant);
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip){
    double total = 0;
    os << "  PVP\tCantidad\t\tArtículo" << std::endl;
    os << "==================================================================" << std::endl;
    for(auto i = ip.begin(); i != ip.end(); i++){
        os << std::fixed << std::setprecision(2) << i->second.precio_venta() <<
        " € " << std::left << std::setw(16) << i->second.cantidad() << "[" << i->first->referencia() << "] " <<
        "\"" << i->first->titulo() << std::endl;

        total += i->second.precio_venta();
    }
    os << "==================================================================" << std::endl;
    os << "Total   " << std::fixed << std::setprecision(2) << total << " €" << std::endl;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds){
    os << "[Pedidos: " << peds.size() << "]" << std::endl;
    os << "==================================================================" << std::endl;
    os << "  PVP\tCantidad\t\tFecha de venta" << std::endl;
    os << "==================================================================" << std::endl;
    for(auto i = peds.begin(); i != peds.end(); i++){
        os << std::fixed << std::setprecision(2) << " € ";
    }
}


std::ostream& operator <<(std::ostream& os, const LineaPedido& lp){
    return os << std::fixed << std::setprecision(2) << lp.precio_venta()<< " €\t" << lp.cantidad() << std::endl;
}
