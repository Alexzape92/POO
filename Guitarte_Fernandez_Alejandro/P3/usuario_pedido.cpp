#include "usuario_pedido.hpp"

void Usuario_Pedido::asocia(Usuario& us, Pedido& ped){
    usu_ped[&us].insert(&ped);
    ped_usu[&ped] = &us;
}

void Usuario_Pedido::asocia(Pedido& ped, Usuario& us){
    asocia(us, ped);
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& us) const{
    auto i = usu_ped.find(&us);

    if(i != usu_ped.end())
        return i->second;
    else
        return Pedidos{};
}

Usuario* Usuario_Pedido::cliente(Pedido& ped) const{
    auto i = ped_usu.find(&ped);

    if(i != ped_usu.end())
        return i->second;
    else
        return nullptr;
}