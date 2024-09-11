
#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "tarjeta.hpp"
#include "usuario.hpp"
#include "../P1/fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include<iomanip>
#include<iostream>

class Tarjeta;
class Fecha;
class Pedido_Articulo;
class Usuario_Pedido;


class Pedido{
public:
    Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& f= Fecha());

    //OBSERVADORES
    unsigned numero() const { return num_; }
    const Tarjeta* tarjeta() const { return tarjeta_; }
    Fecha fecha() const {return fecha_;}
    double total() const {return total_;}
    static unsigned n_total_pedidos() {return N_pedidos;}


    // CLASS VACIO
    class Vacio{
    public:
        Vacio( Usuario& u_): u(&u_){}
        const Usuario& usuario() const noexcept{return *u;}
    private:
        Usuario* u;
    };

    // CLASS IMPOSTOR
    class Impostor{
    public:
        Impostor( Usuario& us):u(&us){}
        const Usuario& usuario()const noexcept{ return *u;}
    private:
        Usuario* u;
    };

    // CLASS SIN STOCK
    class SinStock{
    public:
        SinStock( Articulo& a_):a(&a_){}
        const Articulo& articulo ()const noexcept{return *a;}
    private:
        Articulo* a;

    };

private:
    int num_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
    static int N_pedidos;
};

std::ostream& operator<<(std::ostream& os, const Pedido& P);

#endif






