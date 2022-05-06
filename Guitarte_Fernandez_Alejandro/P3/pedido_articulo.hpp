#ifndef PA_HPP_
#define PA_HPP_
#include "pedido.hpp"
#include "articulo.hpp"
#include <iostream>

class LineaPedido;

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
private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> ped_art;
    std::map<Articulo*, Pedidos, OrdenaArticulos> art_ped;
};

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