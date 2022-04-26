#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <cassert>
#include <ctime>
#include <iostream>

class Fecha{
static std::time_t tiempo_calendario;
static std::tm* tiempo_descompuesto;
static int diact;
static int mesact;
static int annoact;
public:
    static const int AnnoMinimo;
    static const int AnnoMaximo;
    class Invalida;
    explicit Fecha(int d = diact, int m = mesact, int a = annoact);
    Fecha(const char* s);
    int dia() const noexcept;
    int mes() const noexcept;
    int anno() const noexcept;
    Fecha& operator ++();       //Pre, devuelve el modificado
    Fecha operator ++(int);     //Post, devuelve copia porque devuelve el original, no el modificado
    Fecha& operator --();
    Fecha operator --(int);
    Fecha operator +(int n) const;
    Fecha operator -(int n) const;
    Fecha& operator +=(int n);
    Fecha& operator -=(int n);
    const char* cadena() const noexcept {return getCad();};
    friend bool operator <(const Fecha& a, const Fecha& b);
    friend bool operator <=(const Fecha& a, const Fecha& b);
    friend bool operator >(const Fecha& a, const Fecha& b);
    friend bool operator >=(const Fecha& a, const Fecha& b);
    friend bool operator ==(const Fecha& a, const Fecha& b);
    friend bool operator !=(const Fecha& a, const Fecha& b);
    //Operadores de E/S:
    friend std::istream& operator >>(std::istream& is, Fecha& f);
    friend std::ostream& operator <<(std::ostream& os, const Fecha& f);
private:
    int dia_, mes_, anno_;
    static const int diasmes[];

    void corregir_fecha(Fecha& f);
    const char* getCad() const noexcept;
};


class Fecha::Invalida{
public:
    Invalida(const char* s): fallo(s) {}
    const char* por_que() const {return fallo;}
private:
    const char* fallo;
};


inline int Fecha::dia() const noexcept{
    return dia_;
}

inline int Fecha::mes() const noexcept{
    return mes_;
}

inline int Fecha::anno() const noexcept{
    return anno_;
}



#endif
