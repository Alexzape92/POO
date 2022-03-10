#include "Fecha.hpp"
#include <cstdio>
#include <ctime>

//-----MIEMBROS ESTÁTICOS--------------------------------------------------------------------------
std::time_t Fecha::tiempo_calendario = std::time(nullptr);
std::tm* Fecha::tiempo_descompuesto = std::localtime(&tiempo_calendario);
int Fecha::diact = tiempo_descompuesto->tm_mday;
int Fecha::mesact = tiempo_descompuesto->tm_mon + 1;
int Fecha::annoact = tiempo_descompuesto->tm_year + 1900;
int Fecha::Annominimo = 1902;
int Fecha::Annomaximo = 2037;

int Fecha::diasmes[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//-------------------------------------------------------------------------------------------------

Fecha::Fecha(int d/* = diact*/, int m/* = mesact*/, int a/* = annoact*/): dia_(d), mes_(m), anno_(a){
    if(dia_ == 0)
        dia_ = diact;
    if(mes_ == 0)
        mes_ = mesact;
    if(anno_ == 0)
        anno_ = annoact;
    
    //-----------------------------
    //--------EXCEPCIONES----------
    //-----------------------------
    if(m < 1 || m > 12)
        throw Invalida("El mes esta fuera de rango");
    if(m == 2 && d == 29 && a%4 != 0)
        throw Invalida("El año indicado no es bisiesto");
    if(d > diasmes[m-1] || d < 1)
        throw Invalida("El dia se sale del rango del mes");
    if(a < Annominimo || a > Annomaximo)
        throw Invalida("El anno se sale del rango");
}

Fecha::Fecha(const char* s){
    if(sscanf(s, "%d/%d/%d", &dia_, &mes_, &anno_) != 3)
        throw Invalida("Formato incorrecto");
    if(dia_ == 0)
        dia_ = diact;
    if(mes_ == 0)
        mes_ = mesact;
    if(anno_ == 0)
        anno_ = annoact;

    //-----------------------------
    //--------EXCEPCIONES----------
    //-----------------------------
    if(mes_ < 1 || mes_ > 12)
        throw Invalida("El mes esta fuera de rango");
    if(mes_ == 2 && dia_ == 29 && anno_ % 4 != 0)
        throw Invalida("El año indicado no es bisiesto");
    if(dia_ > diasmes[mes_ - 1] || dia_ < 1)
        throw Invalida("El dia se sale del rango del mes");
    if(anno_ < Annominimo || anno_ > Annomaximo)
        throw Invalida("El anno se sale del rango");
}

int Fecha::dia() const {
    return dia_;
}

int Fecha::mes() const {
    return mes_;
}

int Fecha::anno() const {
    return anno_;
}

Fecha& Fecha::operator++() {
    dia_++;

    if(dia_ > diasmes[mes_ - 1] || dia_ < 1)
        throw Invalida("El dia se sale del rango del mes");

    return *this;
}

Fecha Fecha::operator++(int) {
    Fecha c(*this);
    dia_++;

    if(dia_ > diasmes[mes_ - 1] || dia_ < 1)
        throw Invalida("El dia se sale del rango del mes");

    return c;
}