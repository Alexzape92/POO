#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{
public:
    explicit Cadena(unsigned t = 0, char relle = ' ');
    Cadena(const Cadena& c);
    Cadena(const char* c);
    Cadena& operator =(const Cadena& c);
    Cadena& operator =(const char *c);
    operator const char*() const{return s_;}
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
    ~Cadena(){delete[] s_;}
private:
    char *s_;
    unsigned tam_;
};

#endif