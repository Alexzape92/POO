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
    const char* c_str() const noexcept{return s_;}
    unsigned length() const noexcept{return tam_;}
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
    iterator begin() noexcept{return s_;}
    const_iterator begin() const noexcept{ return s_;}
    iterator end() noexcept{return s_ + tam_;}
    const_iterator end() const noexcept{return s_ + tam_;}
    const_iterator cbegin() const noexcept{return begin();}
    const_iterator cend() const noexcept{return end();}
    reverse_iterator rbegin() noexcept{return reverse_iterator(end());}
    const_reverse_iterator rbegin() const noexcept{return const_reverse_iterator(end());}
    reverse_iterator rend() noexcept{return reverse_iterator(begin());}
    const_reverse_iterator rend() const noexcept{return const_reverse_iterator(begin());}
    const_reverse_iterator crbegin() const noexcept{return rbegin();}
    const_reverse_iterator crend() const noexcept{return rend();}
    ~Cadena(){delete[] s_;}
private:
    char *s_;
    unsigned tam_;
};

#endif