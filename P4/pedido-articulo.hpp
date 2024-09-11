//
// Created by Carlitoxere on 02/08/2023.
//

#ifndef P3_PEDIDO_ARTICULO_H
#define P3_PEDIDO_ARTICULO_H
#include <iostream>
#include <map>
#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido {
public:
    explicit LineaPedido(  double precio, unsigned cant=1);


    //OBSERVADORES
     double precio_venta()const noexcept{return precio_venta_;}
    unsigned cantidad()const noexcept{return cantidad_;}
private:
    double precio_venta_;
    unsigned cantidad_;

};

std::ostream& operator <<(std::ostream& os, const LineaPedido&);
class Pedido;

class OrdenaPedidos{
public:
    bool operator()(const Pedido* P1,const Pedido* P2) const;
};

class OrdenaArticulos{
public:
    bool operator()(const Articulo* A1,const Articulo* A2) const;
};

class Pedido_Articulo {
public:
    //SINONIMOS
    typedef std::map<Articulo*,LineaPedido,OrdenaArticulos> ItemsPedido;
    typedef  std::map<Pedido*,LineaPedido,OrdenaPedidos> Pedidos;

    // ENLACES
    void pedir( Pedido& p,  Articulo& art, double precio, unsigned cant=1);
    void pedir( Articulo& art, Pedido& p, double precio, unsigned cant=1);

    // DEVOLVER
       ItemsPedido detalle(  Pedido& p)const noexcept;
     Pedidos ventas ( Articulo& art) const noexcept;

    //MOSTRAR
    void mostrarDetallePedidos(std::ostream& os)const noexcept;
    void mostrarVentasArticulos(std::ostream& os)const noexcept;

private:
    //ASOCIACION PEDIDO-ARTICULO
     typedef std::map<Pedido*,ItemsPedido,OrdenaPedidos> P;
    P pedido;
    //ASOCIACION ARTICULO-PEDIDO
     typedef std::map<Articulo*,Pedidos,OrdenaArticulos> A;
     A articulo;

};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p);


#endif //P3_PEDIDO_ARTICULO_H





