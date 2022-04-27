#include "usuario.hpp"
#include <unistd.h>
#include <random>
#include <cstring>

std::unordered_set<Cadena> Usuario::registrados{};

Clave::Clave(const char* passwd){
    if(strlen(passwd) < 5)
        throw Incorrecta{CORTA};

    std::random_device r;
    std::uniform_int_distribution<int> dist(0, 62);
    const char* caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char salt[2] = {caracteres[dist(r)], caracteres[dist(r)]}; 
    sal = salt;

    try{
        pass = crypt(passwd, sal.c_str());
    }catch(...){
        throw Incorrecta{ERROR_CRYPT};
    }
}

bool Clave::verifica(const char* passwd) const{
    return pass == crypt(passwd, sal.c_str());
}

//USUARIO-------------------------------------------------------------------------------------------------
Usuario::Usuario(const Cadena& ident, const Cadena& nomb, const Cadena& apell, const Cadena& direc, const Clave& cl):
ide{ident}, nom{nomb}, ape{apell}, dir{direc}, pass{cl}{
    if(!registrados.insert(ident).second)
        throw Id_duplicado{ident};
}


void Usuario::compra(Articulo& art, unsigned int cant){
    carrito[&art] = cant;

    if(carrito[&art] == 0)
        carrito.erase(&art);
}

Usuario::~Usuario(){
    for(auto t = tarjs.begin(); t != tarjs.end(); t++)
        t->second->anula_titular();
    
    registrados.erase(this->ide);
}

std::ostream& operator <<(std::ostream& os, const Usuario& us){
    os << us.ide << " [" << us.pass.clave() << "] " << us.nom << " " << us.ape << std::endl;
    os << us.dir << std::endl;
    os << "Tarjetas:" << std::endl;

    for(auto i = us.tarjs.begin(); i != us.tarjs.end(); i++)
        os << *(i->second) << std::endl;

    return os;
}

void mostrar_carro(std::ostream& os, const Usuario& us){
    Usuario::Articulos carro = us.compra();

    os << "Carrito de compra de " << us.id() << " [Artículos: " << us.n_articulos() << "]" << std::endl;
    os << " Cant. Artículo" << std::endl;
    os << "===========================================================" << std::endl;

    for(auto i = carro.begin(); i != carro.end(); i++){
        os << "   " << i->second << "   " << i->first << std::endl;
    }
}

void Usuario::es_titular_de(const Tarjeta& tj){
    if(tj.titular() == this)  //La tarjeta tiene a dicho usuario como titular
        tarjs[tj.numero()] = const_cast<Tarjeta*>(&tj);
}

void Usuario::no_es_titular_de(Tarjeta& tj){
    tarjs.erase(tj.numero());
    tj.anula_titular();
}









