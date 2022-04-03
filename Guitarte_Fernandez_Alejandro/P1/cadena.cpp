#include "cadena.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>

Cadena::Cadena(unsigned t, char relle): s_{new char[t+1]}, tam_{t} {
    for(unsigned i = 0; i < tam_; i++)
        s_[i] = relle;
    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& c): s_{new char[c.tam_+1]}, tam_{c.tam_}{
    for(unsigned i = 0; i < tam_; i++)
        s_[i] = c.s_[i];
    s_[tam_] = '\0';
}

Cadena::Cadena(Cadena&& c): s_{c.s_}, tam_{c.tam_}{
    c.s_ = nullptr; //Evitamos que nos borre la memoria dinámica que ahora tiene la nueva Cadena
    c.tam_ = 0;
}

Cadena::Cadena(const char* c): s_{new char[(unsigned)strlen(c)+1]}, tam_{(unsigned)strlen(c)}{
    for (unsigned i = 0; i < tam_; i++)
        s_[i] = c[i];
    s_[tam_] = '\0';
}

Cadena& Cadena::operator =(const Cadena& c){
    if(this != &c){
        if(tam_ != c.tam_){
            delete[] s_;
            tam_ = c.tam_;
            s_ = new char[tam_+1];
        }
        for(unsigned i = 0; i < tam_; i++)
            s_[i] = c.s_[i];
        s_[tam_] = '\0';
    }
    return *this;
}

Cadena& Cadena::operator =(Cadena&& c){
    if(this != &c){
        delete[] s_;
        s_ = c.s_;
        tam_ = c.tam_;
        c.s_ = nullptr; //Evitamos que nos borre la memoria dinámica que ahora tiene la cadena *this
        c.tam_ = 0;
    }
    return *this;
}

Cadena& Cadena::operator =(const char *c){
    if(tam_ != strlen(c)){
         delete[] s_;
         tam_ = strlen(c);
         s_ = new char[tam_+1];
    }
    for(unsigned i = 0; i < tam_; i++)
        s_[i] = c[i];
    s_[tam_] = '\0';

    return *this;
}

Cadena& Cadena::operator +=(const Cadena& c){
    char *aux = new char[tam_ + c.tam_ + 1];
    
    for(unsigned i = 0; i < tam_; i++)
        aux[i] = s_[i];

    for(unsigned i = tam_; i < tam_ + c.tam_; i++)
        aux[i] = c.s_[i - tam_];
    aux[tam_ + c.tam_] = '\0';

    delete[] s_;
    tam_ = tam_ + c.tam_;
    s_ = new char[tam_ + 1];

    for(unsigned i = 0; i < tam_ + 1; i++)
        s_[i] = aux[i];

    return *this;
}

Cadena Cadena::operator +(const Cadena& c2) const{
    Cadena r{tam_ + c2.tam_};

    for(unsigned i = 0; i < tam_; i++)
        r.s_[i] = s_[i];
    for(unsigned i = tam_; i < r.tam_; i++)
        r.s_[i] = c2.s_[i - tam_];
    r.s_[r.tam_] = '\0';

    return r;
}

bool operator <(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1.s_, c2.s_) < 0);
}

bool operator >(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1.s_, c2.s_) > 0);
}

bool operator <=(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1.s_, c2.s_) <= 0);
}

bool operator >=(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1.s_, c2.s_) >= 0);
}

bool operator ==(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1.s_, c2.s_) == 0);
}

bool operator !=(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1.s_, c2.s_) != 0);
}

char& Cadena::at(unsigned i){
    if((int)i < 0 || i >= tam_)
        throw std::out_of_range{"i no está en el rango de la cadena"};
    
    return s_[i];
}

char Cadena::at(unsigned i) const{
    if((int)i < 0 || i >= tam_)
        throw std::out_of_range{"i no está en el rango de la cadena"};
    
    return s_[i];
}

Cadena Cadena::substr(unsigned i, unsigned t) const{
    if((int)i < 0 || (int)t < 0 || i+t >= tam_)
        throw std::out_of_range{"La posición inicial + tamaño > tamaño de la cadena"};
    Cadena r{t};
    for(unsigned cont = 0; cont < t; cont++)
        r.s_[cont] = s_[cont+i];
    
    return r;
}

std::istream& operator >>(std::istream& is, Cadena& c){
    char *aux = new char[33], car = 'c';
    unsigned i = 0;
    for(i = 0; i < 33; i++) //Llenamos la cadena con el carácter terminador, de manera que si no se llena, el último siempre será \0
        aux[i] = '\0';

    i = 0;
    while((car = is.get()) != EOF && isspace(car));   //Leemos hasta encontrar un caracter distinto de ' '
    is.putback(car);                                  //Devolvemos el último carácter al flujo de entrada                             

    while((car = is.get()) != EOF && !isspace(car) && i < 32){  //Metemos la palabra en la cadena
        aux[i] = car;
        i++;
    }
    is.putback(car);    //Devolvemos el último caracter al flujo de entrada, ya sea el espacio que delimita 2 palabras, el EOF o un carácter que no se ha leído 
                        //porque se han alcanzado los 32 carácteres

    c = Cadena(aux);

    delete[] aux;
    return is;
}

std::ostream& operator <<(std::ostream& os, const Cadena& c){
    os << c.s_;

    return os;
}