//
// Created by poo on 24/04/23.
//

#ifndef P2_USUARIO_H
#define P2_USUARIO_H

#include <map>
#include <unordered_map>
#include <unordered_set>
#include "articulo.hpp"
#include "../P1/cadena.hpp"
#include "cstring"
#include "cstdlib"

#include "tarjeta.hpp"
#include "unistd.h"

class Numero;
class Tarjeta;
//-------------CLASE CLAVE-------------------
class Clave{
public:
    Clave(const char* cad );

    enum Razon{CORTA,ERROR_CRYPT};


    class Incorrecta{
    public:
        Incorrecta( Clave::Razon r):reason(r){}
        Clave::Razon razon() const noexcept{ return reason;}

    private:
        Clave::Razon reason;
    };

    //OBSERVADOR CLAVE CIFRADA
    const Cadena& clave() const noexcept{return contr_cifrada;}
    bool verifica(const char* cad)const noexcept;

private:
    Cadena contr_cifrada;

};

//----------------------CLASS USUARIO------------------------------------------

class Usuario {
public:
    //SINONIMOS
    typedef std::map<Numero,Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*,unsigned int> Articulos;
    //CONSTRUCTORES
    Usuario(const Cadena& i, const Cadena& nom, const Cadena& ap, const Cadena& d, const Clave& c);
    Usuario(const Usuario& u)=delete;
    Usuario& operator =(const Usuario& u)=delete;
    ~Usuario();


    //OBSERVADORES
    const Cadena& id()const noexcept{return _identificador;}
    const Cadena& nombre() const noexcept{return _nombre;}
    const Cadena& apellidos() const noexcept{return _apellidos;}
    const Cadena& direccion() const noexcept{return _direccion;}
     const Tarjetas& tarjetas()const noexcept{return _tarjetas;}
     Articulos& compra() const noexcept{return _articulos;}



    //CLASS Id_duplicado
    class Id_duplicado{
    public:
        Id_duplicado(const Cadena& cad): id_duplicado(cad){}
        const Cadena& idd() const noexcept{return id_duplicado;}

    private:
        Cadena id_duplicado;
    };

    //ENLACES CON TARJETA
    void es_titular_de(Tarjeta& t);//enlaza con tarjeta
    void no_es_titular_de(Tarjeta& t);//desenlazar tarjeta

    //ASOCIACION CON ARTICULOS
    void compra(const Articulo& art, unsigned int cant=1);
    void vaciar_carro();
    size_t n_articulos() const noexcept{return _articulos.size();}

    // OPERATOR <<
     friend std::ostream& operator <<(std::ostream& os, const Usuario& U);






private:
     const Cadena _identificador;
     const Cadena _nombre;
    const Cadena _apellidos;
    const Cadena _direccion;
    Clave _constrasena;
     mutable Tarjetas _tarjetas;
     mutable Articulos _articulos;
    static std::unordered_set<Cadena> contenedor_identificadores;

};

void mostrar_carro(std::ostream& os, const Usuario& U);


#endif //P2_USUARIO_H





