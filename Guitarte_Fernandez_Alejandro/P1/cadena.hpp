#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <iterator>

class Cadena{
public:
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    explicit Cadena(unsigned t = 0, char relle = ' ');
    Cadena(const Cadena& c);
    Cadena(Cadena&& c);
    Cadena(const char* c);
    Cadena& operator =(const Cadena& c);
    Cadena& operator =(Cadena&& c);
    Cadena& operator =(const char *c);
    const char* c_str() const{return s_;}
    unsigned length() const {return tam_;}
    Cadena& operator +=(const Cadena& c);
    Cadena operator +(const Cadena& c2) const;
    friend bool operator <(const Cadena& c1, const Cadena& c2);
    friend bool operator >(const Cadena& c1, const Cadena& c2);
    friend bool operator <=(const Cadena& c1, const Cadena& c2);
    friend bool operator >=(const Cadena& c1, const Cadena& c2);
    friend bool operator ==(const Cadena& c1, const Cadena& c2);
    friend bool operator !=(const Cadena& c1, const Cadena& c2);
    char& operator [](unsigned i) {return s_[i];}
    char operator [](unsigned i) const {return s_[i];}
    char& at(unsigned i);
    char at(unsigned i) const;
    Cadena substr(unsigned i, unsigned t) const;
    friend std::istream& operator >>(std::istream& is, Cadena& c);
    friend std::ostream& operator <<(std::ostream& os, const Cadena& c);
    iterator begin() {return s_;}
    const_iterator begin() const{ return s_;}
    iterator end() {return s_ + tam_;}
    const_iterator end() const {return s_ + tam_;}
    const_iterator cbegin() const {return s_;}
    const_iterator cend() const {return s_ + tam_;}
    reverse_iterator rbegin() {return reverse_iterator(end());}
    reverse_iterator rend() {return reverse_iterator(begin());}
    const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
    const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
    const_reverse_iterator crbegin() const {return const_reverse_iterator(cend());}
    const_reverse_iterator crend() const {return const_reverse_iterator(cbegin());}
    ~Cadena(){delete[] s_;}
private:
    char *s_;
    unsigned tam_;
};

#endif