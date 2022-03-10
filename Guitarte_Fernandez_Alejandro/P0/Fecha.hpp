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
    static int Annominimo;
    static int Annomaximo;
    class Invalida;
    explicit Fecha(int d = diact, int m = mesact, int a = annoact);
    Fecha(const char* s);
    int dia() const;
    int mes() const;
    int anno() const;
    Fecha& operator ++();       //Pre, devuelve el modificado
    Fecha operator ++(int);     //Post, devuelve copia porque devuelve el original, no el modificado
private:
    int dia_, mes_, anno_;
    static int diasmes[];
};


class Fecha::Invalida{
public:
    Invalida(const char* s): fallo(s) {}
    const char* por_que() const {return fallo;}
private:
    const char* fallo;
};



#endif