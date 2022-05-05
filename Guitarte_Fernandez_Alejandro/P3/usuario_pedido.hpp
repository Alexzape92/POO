#ifndef UP_HPP_
#define UP_HPP_
#include "usuario.hpp"
#include "pedido.hpp"
#include <map>
#include <set>

class Usuario_Pedido{
public:
    typedef std::set<Pedido*> Pedidos;

    //Usamos el constructor por defecto
    //Modificadores
    void asocia(Usuario& us, Pedido& ped);
    void asocia(Pedido& ped, Usuario& us);

    //Observadores
    Pedidos pedidos(Usuario& us) const;
    Usuario* cliente(Pedido& ped) const;
private:
    std::map<Usuario*, Pedidos> usu_ped;
    std::map<Pedido*, Usuario*> ped_usu;
};



#endif