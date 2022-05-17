#include "pedido.hpp"
#include <iomanip>

int Pedido::ultimo{1};  //El primer pedido será el 1


Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa,const Usuario& us, const Tarjeta& tarj, Fecha fec):
num{ultimo++}, tj{&tarj}, fch{fec}, imp{0}{
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
        throw Tarjeta::Caducada{fec};
    }

    if(!tarj.activa()){
        ultimo--;   //Dejamos el contador por donde iba
        throw Tarjeta::Desactivada{};
    }

    up.asocia(*this, const_cast<Usuario&>(us));    //Relacion Usuario-Pedido
    for(auto i = us.compra().begin(); i != us.compra().end(); i++){
        if(i->first->stock() < i->second){ //No tenemos stock suficiente
            ultimo--;   //Dejamos el contador por donde iba
            throw SinStock{*(i->first)};
        }

        i->first->stock() -= i->second; //Disminuimos el stock
        pa.pedir(*(i->first), *this, i->first->precio(), i->second);
        imp += i->first->precio();      //Importe del producto
    }
}


std::ostream& operator <<(std::ostream& os, const Pedido& ped){
    os << "Núm. pedido: " << ped.numero() << std::endl;
    os << std::left << std::setw(13) << "Fecha:" << ped.fecha() << std::endl;
    os << std::left << std::setw(13) << "Pagado con:" << ped.tarjeta().tipo() << " n.º: " << ped.tarjeta().numero() << std::endl;
    os << std::left << std::setw(13) << "Importe:" << std::fixed << std::setprecision(2) << ped.total() << " €" << std::endl;

    return os;
}