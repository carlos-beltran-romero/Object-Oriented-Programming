

#ifndef P2_ARTICULO_H
#define P2_ARTICULO_H

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iostream>
#include <locale>
#include <iomanip>
#include <set>

class Autor{
public:
    Autor(const Cadena& n,const Cadena& a, const Cadena& d)noexcept: nombre_(n), apellidos_(a), direccion_(d){}
    const Cadena& nombre()const noexcept{return nombre_;}
    const Cadena& apellidos()const noexcept{return apellidos_;}
    const Cadena& direccion()const noexcept{return direccion_;}


private:
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
};

class Articulo {
public:
    typedef std::set<Autor*> Autores;

    Articulo( const Autores& aut, Cadena cod,Cadena t, Fecha f_pub,double p);

    //OBSERVADORES
    const Cadena& referencia() const noexcept{ return referencia_; }
    const Cadena& titulo() const noexcept{return titulo_;}
    const Fecha& f_publi() const noexcept{ return f_publi_;}
    double precio() const noexcept{return precio_; }

    //OBSERVADORES SOBRECARGADOS
    double& precio()noexcept{return precio_;}

    //MÉTODO VIRTUAL PURO
    virtual void impresion_especifica(std::ostream&) const =0;
    const Autores& autores()const noexcept{return A;}


    virtual ~Articulo(){};

    class Autores_vacios{};

private:
     const Autores A;
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha f_publi_;
    double precio_;


};
// OPERATOR INSERCIÓN
std::ostream& operator <<(std::ostream& onto, const Articulo& art);

//--------------------  CLASE ARTICULO ALMACENABLE ------------------------------------------------------

class ArticuloAlmacenable: public Articulo{
public:
    ArticuloAlmacenable(const Autores& aut, Cadena cod,Cadena t, Fecha f_pub,double p, size_t s=0):Articulo(aut,cod,t,f_pub,p), stock_(s){};


    size_t & stock()noexcept{return stock_;}
    size_t stock()const noexcept{return stock_;}
protected:
    size_t stock_;


};

//---------------------------- CLASE LIBRO -----------------------------------------------------------------
// tengo el atributo _stock de ArticuloAlmacenable pero solo puedo llamarlo dentro de la clase
class Libro final: public ArticuloAlmacenable{
public:

    Libro(const Autores& aut, Cadena cod,Cadena t, Fecha f_pub,double p,size_t pag, size_t s=0): ArticuloAlmacenable(aut,cod,t,f_pub,p,s), n_pag_(pag){}
     void impresion_especifica(std::ostream&)const  override;
    size_t n_pag()const noexcept{return n_pag_;}

private:
     const size_t n_pag_;
};


//-------------------------------- CLASE REVISTA----------------------
class Revista final: public ArticuloAlmacenable{
public:
    Revista(const Autores& aut, Cadena cod,Cadena t, Fecha f_pub,double p,unsigned num,unsigned dias, size_t s=0): ArticuloAlmacenable(aut,cod,t,f_pub,p,s),numero_(num),periodicidad_(dias){}

    void impresion_especifica(std::ostream&)const  override;

    //Observadores
    unsigned numero()const noexcept{return numero_;}
    unsigned periodicidad() const noexcept{ return periodicidad_;}


private:
     const unsigned numero_;
     const unsigned periodicidad_;


};

//-------------------------------------CLASE LIBRODIGITAL-----------------------------------------------
class LibroDigital final: public Articulo{
public:

    LibroDigital(const Autores& aut, Cadena cod,Cadena t, Fecha f_pub,double p,const Fecha& f):
    Articulo(aut,cod,t,f_pub,p), f_expir_(f){}
    //Observador
     const Fecha& f_expir ()const  noexcept{return f_expir_;}

    void impresion_especifica(std::ostream&)const  override;

private:
    const Fecha f_expir_;
};


#endif //P2_ARTICULO_H
