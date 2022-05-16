#ifndef PA_HPP_
#define PA_HPP_
#include "pedido.hpp"
#include "articulo.hpp"
#include <iostream>

class LineaPedido;

//CLASES DE OBJETOS A FUNCIÓN
class OrdenaArticulos{
    bool operator ()(const Articulo& a1, const Articulo& a2){return a1.referencia() < a2.referencia();}
};

class OrdenaPedidos{
    bool operator ()(const Pedido& p1, const Pedido& p2){return p1.numero() < p2.numero();}
};

//PEDIDOARTICULO-----------------------------------------------------------------------------------------
class Pedido_Articulo{
public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido; //Añadir objeto función>
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos; //añadir objeto función

    //Asociadores
    void pedir(Pedido& ped, Articulo& art, double prec, int cant = 1);
    void pedir(Articulo& art, Pedido& ped, double prec, int cant = 1);

    //Observadores
    const ItemsPedido& detalle(Pedido& ped) const;
    const Pedidos& ventas(Articulo& art) const;
    void mostrarDetallePedidos(std::ostream& os) const;
    void mostrarVentasArticulos(std::ostream& os) const;
private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> ped_art;
    std::map<Articulo*, Pedidos, OrdenaArticulos> art_ped;
};

//Operadores de inserción en flujo de salida
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds);

//Definiciones en línea para Pedido_Articulo
inline const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped) const{
    auto i = ped_art.find(&ped);

    if(i != ped_art.end())
        return i->second;
    else
        return ItemsPedido{};
}

inline const Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& art) const{
    auto i = art_ped.find(&art);

    if(i != art_ped.end())
        return i->second;
    else
        return Pedidos{};
}

//LINEAPEDIDO--------------------------------------------------------------------------------------
class LineaPedido{
public:
    //Constructor
    explicit LineaPedido(double prec, int cant = 1);

    //Observadores
    double precio_venta() const;
    int cantidad() const;
private:
    double pv;
    int canti;
};

//Operador de inserción en flujo de salida
std::ostream& operator <<(std::ostream& os, const LineaPedido& lp);

//Definiciones en-línea para LineaPedido
inline LineaPedido::LineaPedido(double prec, int cant):pv{prec}, canti{cant}{}

inline double LineaPedido::precio_venta() const{
    return pv;
}

inline int LineaPedido::cantidad() const{
    return canti;
}


#endif