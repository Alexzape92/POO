#include "pedido-articulo.hpp"
#include <iomanip>

bool OrdenaPedidos::operator ()(const Pedido* p1, const Pedido* p2) const{
    return p1->numero() < p2->numero();
}

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double prec, int cant){
    ped_art[&ped].insert(std::make_pair(&art, LineaPedido(prec, cant)));
    art_ped[&art].insert(std::make_pair(&ped, LineaPedido(prec, cant)));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double prec, int cant){
    pedir(ped, art, prec, cant);
}

Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& ped) const{
    auto i = ped_art.find(&ped);

    if(i != ped_art.end())
        return i->second;
    else
        return ItemsPedido{};
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art) const{
    auto i = art_ped.find(&art);

    if(i != art_ped.end())
        return i->second;
    else
        return Pedidos{};
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip){
    double total = 0;
    os << "  PVP\tCantidad\t\tArtículo" << std::endl;
    os << "==================================================================" << std::endl;
    for(auto i = ip.begin(); i != ip.end(); i++){
        os << std::fixed << std::setprecision(2) << i->second.precio_venta() <<
        " € " << std::left << std::setw(16) << i->second.cantidad() << "[" << i->first->referencia() << "] " <<
        "\"" << i->first->titulo() << "\"" << std::endl;

        total += i->second.precio_venta();
    }
    os << "==================================================================" << std::endl;
    os << "Total   " << std::fixed << std::setprecision(2) << total << " €" << std::endl;

    return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds){
    double total = 0;
    os << "[Pedidos: " << peds.size() << "]" << std::endl;
    os << "==================================================================" << std::endl;
    os << "  PVP\tCantidad\t\tFecha de venta" << std::endl;
    os << "==================================================================" << std::endl;
    for(auto i = peds.begin(); i != peds.end(); i++){
        os << std::fixed << std::setprecision(2) << i->second.precio_venta() << " € " << std::left << std::setw(16) << i->second.cantidad() << i->first->fecha() << std::endl;
        total += i->second.precio_venta();
    }
    os << "==================================================================" << std::endl;
    os << std::fixed << std::setprecision(2) << total << " €" << std::endl;

    return os;
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os) const{
    double total = 0;
    for(auto i = ped_art.begin(); i != ped_art.end(); i++){
        os << "Pedido núm. " << i->first->numero()<< std::endl; 
        os << i->first->tarjeta()->titular()->nombre() << "\t\t" << "Fecha: " << i->first->fecha() << std::endl;
        os << detalle(*(i->first)) << std:: endl;

        total += i->first->total();
    }

    os << "TOTAL VENTAS\t\t" << std::fixed << std::setprecision(2) << total << " € " << std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os) const{
    for(auto i = art_ped.begin(); i != art_ped.end(); i++){
        os << "Ventas de [" << i->first->referencia() << "] \"" << i->first->titulo() << "\"" << std::endl;
        os << ventas(*(i->first)) << std::endl;
    }
}

std::ostream& operator <<(std::ostream& os, const LineaPedido& lp){
    return os << std::fixed << std::setprecision(2) << lp.precio_venta()<< " €\t" << lp.cantidad() << std::endl;
}
