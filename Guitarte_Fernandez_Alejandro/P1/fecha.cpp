#include "fecha.hpp"
#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>

//-----MIEMBROS ESTÁTICOS--------------------------------------------------------------------------
std::time_t Fecha::tiempo_calendario = std::time(nullptr);
std::tm* Fecha::tiempo_descompuesto = std::localtime(&tiempo_calendario);
int Fecha::diact = tiempo_descompuesto->tm_mday;
int Fecha::mesact = tiempo_descompuesto->tm_mon + 1;
int Fecha::annoact = tiempo_descompuesto->tm_year + 1900;
const int Fecha::AnnoMinimo = 1902;
const int Fecha::AnnoMaximo = 2037;

const int Fecha::diasmes[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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
    if(mes_ < 1 || mes_ > 12)
        throw Invalida("El mes esta fuera de rango");
    if(mes_ == 2 && dia_ == 29 && anno_%4 != 0)
        throw Invalida("El año indicado no es bisiesto");
    if(dia_ > diasmes[mes_-1] || dia_ < 1)
        throw Invalida("El dia se sale del rango del mes");
    if(anno_ < AnnoMinimo || anno_ > AnnoMaximo)
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
    if(anno_ < AnnoMinimo || anno_ > AnnoMaximo)
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
    corregir_fecha(*this);

    return *this;
}

Fecha Fecha::operator++(int) {
    Fecha c(*this);
    dia_++;
    corregir_fecha(*this);

    return c;
}

Fecha& Fecha::operator--() {
    dia_--;
    corregir_fecha(*this);

    return *this;
}

Fecha Fecha::operator--(int) {
    Fecha c(*this);
    dia_--;
    corregir_fecha(*this);

    return c;
}

Fecha& Fecha::operator +=(int n){
    dia_ += n;
    corregir_fecha(*this);

    return *this;
}

Fecha& Fecha::operator -=(int n){
    dia_ -= n;
    corregir_fecha(*this);

    return *this;
}

Fecha operator +(Fecha f, int n){
    f.dia_ += n;
    f.corregir_fecha(f);

    return f;
}

Fecha operator -(Fecha f, int n){
    f.dia_ -= n;
    f.corregir_fecha(f);

    return f;
}

bool operator <(const Fecha& a, const Fecha& b){
    bool res = true;

    if(a.anno_ > b.anno_)
        res = false;
    else if(a.anno_ == b.anno_){
        if(a.mes_ > b.mes_)
            res = false;
        else if(a.mes_ == b.mes_){  
            if(a.dia_ >= b.dia_)
                res = false;
        }
    }
    
    return res;
}

bool operator <=(const Fecha& a, const Fecha& b){
    bool res = true;

    if(a.anno_ > b.anno_)
        res = false;
    else if(a.anno_ == b.anno_){
        if(a.mes_ > b.mes_)
            res = false;
        else if(a.mes_ == b.mes_){  
            if(a.dia_ > b.dia_)
                res = false;
        }
    }
    
    return res;
}

bool operator >(const Fecha& a, const Fecha& b){
    bool res = true;

    if(a.anno_ < b.anno_)
        res = false;
    else if(a.anno_ == b.anno_){
        if(a.mes_ < b.mes_)
            res = false;
        else if(a.mes_ == b.mes_){  
            if(a.dia_ <= b.dia_)
                res = false;
        }
    }
    
    return res;
}

bool operator >=(const Fecha& a, const Fecha& b){
    bool res = true;

    if(a.anno_ < b.anno_)
        res = false;
    else if(a.anno_ == b.anno_){
        if(a.mes_ < b.mes_)
            res = false;
        else if(a.mes_ == b.mes_){  
            if(a.dia_ < b.dia_)
                res = false;
        }
    }
    
    return res;
}

bool operator ==(const Fecha& a, const Fecha& b){
    bool res = true;

    if(a.anno_ != b.anno_)
        res = false;
    else if(a.mes_ != b.mes_)
        res = false;
    else if(a.dia_ != b.dia_)
        res = false;
    
    return res;
}

bool operator !=(const Fecha& a, const Fecha& b){
    bool res = false;

    if(a.anno_ != b.anno_)
        res = true;
    else if(a.mes_ != b.mes_)
        res = true;
    else if(a.dia_ != b.dia_)
        res = true;
    
    return res;
}

std::istream& operator >>(std::istream& is, Fecha& f){
    char *aux = new char[10];
    is >> aux;  //Tenemos en aux la cadena en cuestión
    const char* fmt = aux;

    try{
        f = Fecha(fmt);
    }catch(Fecha::Invalida e){
        is.setstate(std::ios_base::failbit);    //Marcamos el flujo de entrada al estado de error
        f = Fecha();                            //La fecha toma el valor de hoy
        throw;                                  //Relanzamos Fecha::Invalida
    }

    //Aquí estamos seguros de que, al menos, el formato era correcto
    unsigned i = 0, cont = 0;
    while(fmt[i] == '0' && cont < 2){
        cont++;
        i++;
    }
    if(cont == 2 && fmt[i] != '/'){
        is.setstate(std::ios_base::failbit);
        f = Fecha();
        throw Fecha::Invalida("Se han introducido más de 3 dígitos");
    }
    else{
        while(fmt[i] != '/') i++;
        cont = 0;
        while(fmt[i] == '0' && cont < 2){
            cont++;
            i++;
        }
        if(cont == 2 && fmt[i] != '/'){
            is.setstate(std::ios_base::failbit);
            f = Fecha();
            throw Fecha::Invalida("Se han introducido más de 3 dígitos");
        }
    }

    delete[] aux;
    return is;
}

std::ostream& operator <<(std::ostream& os, const Fecha& f){
    os << f.cadena();

    return os;
}

//PRIVADAS---------------------------------------------------------------------------
void Fecha::corregir_fecha(Fecha& f){
    if(f.dia_ == 29 && f.mes_ == 2 && f.anno_ % 4 != 0){
        f.dia_ = 1; f.mes_ = 3;
    }

    while(f.dia_ > f.diasmes[f.mes_ - 1]){
        f.dia_ -= f.diasmes[f.mes_ - 1];
        if(f.mes_ == 2 && f.anno_ % 4 != 0){
            f.dia_++;
        }
        f.mes_++;
        if(f.mes_ > 12){
            f.mes_ = 1;
            f.anno_++;
        }
    }

    while(f.dia_ <= 0){
        if(f.mes_ >= 2)
            f.dia_ += f.diasmes[f.mes_ - 2];
        else
            f.dia_ += f.diasmes[11];
        if(f.mes_ == 3 && f.anno_ % 4 != 0){
            f.dia_--;
        }
        f.mes_--;
        if(f.mes_ == 0){
            f.mes_ = 12;
            f.anno_--;
        }
    }

    if(f.anno_ > f.AnnoMaximo)
        throw Fecha::Invalida("Se ha excedido del anno maximo");

    if(f.anno_ < f.AnnoMinimo)
        throw Fecha::Invalida("Se ha excedido del anno minimo");
}

const char *Fecha::getCad() const{
    char *res = new char[50], *aux = new char[50];
    std::tm* fec = new tm;

    memset(fec, 0, sizeof(*fec));
    fec->tm_mday = dia_;
    fec->tm_mon = mes_ - 1;
    fec->tm_year = anno_ - 1900;

    mktime(fec);
    
    switch(fec->tm_wday){
        case 0: strcpy(res, "domingo "); break;
        case 1: strcpy(res, "lunes "); break;
        case 2: strcpy(res, "martes "); break;
        case 3: strcpy(res, "miércoles "); break;
        case 4: strcpy(res, "jueves "); break;
        case 5: strcpy(res, "viernes "); break;
        case 6: strcpy(res, "sábado "); break;
    }

    sprintf(aux, "%d", dia_);
    strcat(res, aux);
    strcat(res, " de ");

    switch(mes_){
        case 1: strcat(res, "enero de "); break;
        case 2: strcat(res, "febrero de "); break;
        case 3: strcat(res, "marzo de "); break;
        case 4: strcat(res, "abril de "); break;
        case 5: strcat(res, "mayo de "); break;
        case 6: strcat(res, "junio de "); break;
        case 7: strcat(res, "julio de "); break;
        case 8: strcat(res, "agosto de "); break;
        case 9: strcat(res, "septiembre de "); break;
        case 10: strcat(res, "octubre de "); break;
        case 11: strcat(res, "noviembre de "); break;
        case 12: strcat(res, "diciembre de "); break;
    }

    sprintf(aux, "%d", anno_);
    strcat(res, aux);

    delete[] aux;
    delete fec;

    return res;
}
