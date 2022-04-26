#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <iterator>
#include <stdexcept>

class Cadena{
public:
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    //CONSTRUCTORES
    explicit Cadena(unsigned t = 0, char relle = ' ');
    Cadena(const Cadena& c);
    Cadena(Cadena&& c);
    Cadena(const char* c);

    //ASIGNACIÓN
    Cadena& operator =(const Cadena& c);
    Cadena& operator =(Cadena&& c);
    Cadena& operator =(const char *c);

    //VARIOS
    const char* c_str() const noexcept{return s_;}
    unsigned length() const noexcept{return tam_;}
    Cadena& operator +=(const Cadena& c);
    Cadena operator +(const Cadena& c2) const;
    char& operator [](unsigned i) {return s_[i];}
    char operator [](unsigned i) const {return s_[i];}
    char& at(unsigned i);
    char at(unsigned i) const;
    Cadena substr(unsigned i, unsigned t) const;

    //ITERADORES
    iterator begin() noexcept{return s_;}
    const_iterator begin() const noexcept{ return const_iterator(s_);}
    iterator end() noexcept{return s_ + tam_;}
    const_iterator end() const noexcept{return const_iterator(s_ + tam_);}
    const_iterator cbegin() const noexcept{return const_iterator(s_);}
    const_iterator cend() const noexcept{return const_iterator(s_ + tam_);}
    reverse_iterator rbegin() noexcept{return reverse_iterator(end());}
    const_reverse_iterator rbegin() const noexcept{return const_reverse_iterator(end());}
    reverse_iterator rend() noexcept{return reverse_iterator(begin());}
    const_reverse_iterator rend() const noexcept{return const_reverse_iterator(begin());}
    const_reverse_iterator crbegin() const noexcept{return const_reverse_iterator(end());}
    const_reverse_iterator crend() const noexcept{return const_reverse_iterator(begin());}
    ~Cadena(){delete[] s_;}
private:
    char *s_;
    unsigned tam_;
};

//Operadores de comparación
bool operator <(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator <=(const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);
bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);

//Operadores de inserción/extracción de flujo
std::istream& operator >>(std::istream& is, Cadena& c);
std::ostream& operator <<(std::ostream& os, const Cadena& c);


// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std { // Estaremos dentro del espacio de nombres std
    template <> // Es una especialización de una plantilla para Cadena
    struct hash<Cadena> { // Es una clase con solo un operador publico
        size_t operator() (const Cadena& cad) const // El operador función
        {
            hash<string> hs; // Creamos un objeto hash de string
            const char* p = cad.c_str(); // Obtenemos la cadena de la Cadena
            string s(p); // Creamos un string desde una cadena
            size_t res = hs(s); // El hash del string. Como hs.operator()(s);
            return res; // Devolvemos el hash del string
        }
    };
}

#endif

