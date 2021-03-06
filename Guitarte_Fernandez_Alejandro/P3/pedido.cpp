#include "pedido.hpp"
#include <iomanip>

int Pedido::ultimo{1};  //El primer pedido será el 1


Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& us, const Tarjeta& tarj, const Fecha& fec):
num{ultimo++}, tarjeta_{&tarj}, fch{fec}, imp{0}{
    if(&us != tarj.titular()){
        ultimo--;   //Dejamos el contador por donde iba
        throw Impostor{const_cast<Usuario&>(us)};
    }

    if(us.compra().empty()){
        ultimo--;   //Dejamos el contador por donde iba
        throw Vacio{const_cast<Usuario&>(us)};
    }

    if(tarj.caducidad() < fec){
        ultimo--;   //Dejamos el contador por donde iba
        throw Tarjeta::Caducada{tarj.caducidad()};
    }

    if(!tarj.activa()){
        ultimo--;   //Dejamos el contador por donde iba
        throw Tarjeta::Desactivada{};
    }

    for(auto i = us.compra().begin(); i != us.compra().end(); i++){
        if(i->first->stock() < i->second){ //No tenemos stock suficiente
            ultimo--;   //Dejamos el contador por donde iba
            auto point = i->first;
            const_cast<Usuario::Articulos&>(us.compra()).clear();   //Vaciamos el carrito
            throw SinStock{point};
        }
    }

    up.asocia(*this, us);    //Relacion Usuario-Pedido
    for(auto i = us.compra().begin(); i != us.compra().end(); i++){
        i->first->stock() -= i->second; //Disminuimos el stock
        pa.pedir(*(i->first), *this, i->first->precio(), i->second);
        imp += i->first->precio() * i->second;      //Importe del producto
    }
    const_cast<Usuario::Articulos&>(us.compra()).clear();   //Vaciamos el carrito
}


std::ostream& operator <<(std::ostream& os, const Pedido& ped){
    os << "Núm. pedido: " << ped.numero() << std::endl;
    os << std::left << std::setw(13) << "Fecha:" << ped.fecha() << std::endl;
    os << std::left << std::setw(13) << "Pagado con:";
    if(ped.tarjeta()->tipo() == Tarjeta::Otro)
        os << "Tipo indeterminado";
    else    
        os << ped.tarjeta()->tipo();
    os << " n.º: " << ped.tarjeta()->numero() << std::endl;
    os << std::left << std::setw(13) << "Importe:" << std::fixed << std::setprecision(2) << ped.total() << " €" << std::endl;

    return os;
}