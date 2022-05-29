#include "articulo.hpp"
#include <iomanip>

Articulo::Articulo(Autores& au, const Cadena& c, const Cadena& t, const Fecha& fec, double pr): 
aus{au}, cod{c}, tit{t}, pub{fec}, prec{pr}{
    if(au.empty())
        throw Autores_vacios{};
}

std::ostream& operator <<(std::ostream& os, const Articulo& art){
    os << "[" << art.referencia() << "] \"" << art.titulo() << "\", de ";
    
    bool primero = true;
    const auto& aut = art.autores();
    for(auto i = aut.begin(); i != aut.end(); i++){
        if(primero){
            os << (*i)->apellidos();
            primero = false;
        }
        else
            os << ", " << (*i)->apellidos();
    }
    os << ". ";

    os << art.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << art.precio() << " €" << "\n\t";
    art.impresion_especifica(os);

    return os;
}

void LibroDigital::impresion_especifica(std::ostream& os) const{
    os << "A la venta hasta el " << f_expir() << ".";
}

void Libro::impresion_especifica(std::ostream& os) const{
    os << n_pag() << " págs., " << stock() << " unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const{
    os << tam() << " MB, " << stock() << " unidades.";
}   