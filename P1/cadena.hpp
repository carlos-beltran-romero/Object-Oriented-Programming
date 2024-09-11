//
// Created by poo on 21/02/23.
//
#ifndef P0_CADENA_H
#define P0_CADENA_H

#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iterator>





class Cadena {
public:
    //CONSTRUCTORES
    explicit Cadena(size_t tam=0,char c=' ');
    Cadena(const Cadena& cad);
    Cadena(const char* c);
    Cadena(Cadena&& cad);

    //OPERADOR ASIGNACION
    Cadena& operator=(const Cadena& cad);
    Cadena& operator=(const char* cad);
    //ASIGNACION DE MOVIMIENTO
    Cadena& operator=(Cadena&& cad);

    //CONVERSOR
    explicit operator const char*()const{return s_;}

    //OBSERVADORES
    size_t length()const noexcept{return tam_;}
    const char* getter_cad() const noexcept{return s_;};




    //OPERADORES ARITMETICOS
    Cadena& operator +=(const Cadena& cad);

    //FUNCIONES MIEMBRO
    const char& operator[](size_t indice) const noexcept;
    char& operator[](size_t indice) noexcept;
    const char& at(size_t indice)const;
    char& at(size_t indice);
    Cadena substr(size_t indice, size_t tamanio)const;

    // TIPOS ITERATORS
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std:: reverse_iterator<const_iterator> const_reverse_iterator;

    // FUNCIONES ITERATORS
    iterator begin(){return s_;}
    const_iterator cbegin() const {return s_;}
    const_iterator begin() const {return cbegin();}
    reverse_iterator rbegin() { return reverse_iterator(end());}
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end());}
    const_reverse_iterator rbegin() const {return crbegin();}

    iterator end() {return s_ + tam_ ;}
    const_iterator cend() const { return s_ + tam_ ;}
    const_iterator end() const {return cend();}
    reverse_iterator rend() {return reverse_iterator(begin());}
    const_reverse_iterator crend() const {return const_reverse_iterator(begin());}
    const_reverse_iterator rend() const {return crend();}



    ~Cadena();



private:
    char* s_;
    size_t tam_;


};
Cadena operator +(const Cadena& A,const Cadena& B);
bool operator ==(const Cadena& A,const Cadena& B);
bool operator <(const Cadena& A,const Cadena& B);
bool operator >(const Cadena& A,const Cadena& B);
bool operator !=(const Cadena& A,const Cadena& B);
bool operator <=(const Cadena& A,const Cadena& B);
bool operator >=(const Cadena& A,const Cadena& B);
// OPERADOR DE EXTRACCIÓN
std::istream& operator >>(std::istream&  into,Cadena& c);

std::ostream& operator <<(std::ostream& cout,const Cadena& c);

// Para P2.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std { // Estaremos dentro del espacio de nombres std
    template <> // Es una especialización de una plantilla para Cadena
    struct hash<Cadena> { // Es una clase con solo un operador publico
        size_t operator() (const Cadena& cad) const // El operador función
        {
            hash<string> hs; // Creamos un objeto hash de string
            const char* p = cad.getter_cad(); // Obtenemos la cadena de la Cadena
            string s(p); // Creamos un string desde una cadena
            size_t res = hs(s); // El hash del string. Como hs.operator()(s);
            return res; // Devolvemos el hash del string
        }
    };
}



#endif //P0_CADENA_H
