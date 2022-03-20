#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <cassert>
#include <ctime>

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
    int dia() const;
    int mes() const;
    int anno() const;
    Fecha& operator ++();       //Pre, devuelve el modificado
    Fecha operator ++(int);     //Post, devuelve copia porque devuelve el original, no el modificado
    Fecha& operator --();
    Fecha operator --(int);
    friend Fecha operator +(Fecha f, int n);
    friend Fecha operator -(Fecha f, int n);
    Fecha& operator +=(int n);
    Fecha& operator -=(int n);
    operator const char*() const{return getCad(); };
    friend bool operator <(const Fecha& a, const Fecha& b);
    friend bool operator <=(const Fecha& a, const Fecha& b);
    friend bool operator >(const Fecha& a, const Fecha& b);
    friend bool operator >=(const Fecha& a, const Fecha& b);
    friend bool operator ==(const Fecha& a, const Fecha& b);
    friend bool operator !=(const Fecha& a, const Fecha& b);
private:
    int dia_, mes_, anno_;
    static const int diasmes[];

    void corregir_fecha(Fecha& f);
    const char* getCad() const;
};


class Fecha::Invalida{
public:
    Invalida(const char* s): fallo(s) {}
    const char* por_que() const {return fallo;}
private:
    const char* fallo;
};



#endif