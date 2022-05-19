#ifndef PA_HPP_
#define PA_HPP_

#include "articulo.hpp"
#include "pedido.hpp"
#include <iostream>

class Pedido;
class Articulo;

//LINEAPEDIDO--------------------------------------------------------------------------------------
class LineaPedido{
public:
    //Constructor
    explicit LineaPedido(double prec, unsigned cant = 1);

    //Observadores
    double precio_venta() const;
    int cantidad() const;
private:
    double pv;
    unsigned canti;
};

//Operador de inserción en flujo de salida
std::ostream& operator <<(std::ostream& os, const LineaPedido& lp);

//Definiciones en-línea para LineaPedido
inline LineaPedido::LineaPedido(double prec, unsigned cant):pv{prec}, canti{cant}{}

inline double LineaPedido::precio_venta() const{
    return pv;
}

inline int LineaPedido::cantidad() const{
    return canti;
}

//CLASES DE OBJETOS A FUNCIÓN
struct OrdenaArticulos{
    bool operator ()(const Articulo* a1, const Articulo* a2) const;
};

struct OrdenaPedidos{
    bool operator ()(const Pedido* p1, const Pedido* p2) const;
};

inline bool OrdenaArticulos::operator()(const Articulo* a1, const Articulo* a2) const{
    return a1->referencia() < a2->referencia();
}

//PEDIDOARTICULO-----------------------------------------------------------------------------------------
class Pedido_Articulo{
public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

    //Asociadores
    void pedir(Pedido& ped, Articulo& art, double prec, unsigned cant = 1);
    void pedir(Articulo& art, Pedido& ped, double prec, unsigned cant = 1);

    //Observadores
    ItemsPedido detalle(Pedido& ped) const;
    Pedidos ventas(Articulo& art) const;
    void mostrarDetallePedidos(std::ostream& os) const;
    void mostrarVentasArticulos(std::ostream& os) const;
private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> ped_art;
    std::map<Articulo*, Pedidos, OrdenaArticulos> art_ped;
};

//Operadores de inserción en flujo de salida
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds);


#endif