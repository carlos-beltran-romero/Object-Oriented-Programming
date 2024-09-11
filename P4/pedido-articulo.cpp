//
// Created by Carlitoxere on 02/08/2023.
//

#include "pedido-articulo.hpp"

LineaPedido::LineaPedido(double precio, unsigned int cant): precio_venta_(precio),cantidad_(cant){}


std::ostream& operator <<(std::ostream& os, const LineaPedido& lp){

    os<<std::fixed<<std::setprecision(2)<<lp.precio_venta()<<" €"<<"\t"<<lp.cantidad()<<std::endl;
    return os;

}

// CLASE ORDENA PEDIDOS
bool OrdenaPedidos::operator()(const Pedido* P1, const Pedido* P2) const {
    return P1->numero()<P2->numero();
}

// CLASE ORDENA ARTICULOS
bool OrdenaArticulos::operator()(const Articulo* A1, const Articulo* A2) const {
    return A1->referencia()<A2->referencia();
}

// CLASE PEDIDO_ARTICULO

void Pedido_Articulo::pedir( Pedido &p,Articulo &art, double precio, unsigned int cant) {
    pedido[&p].insert(std::make_pair(&art,LineaPedido(precio,cant)));
    articulo[&art].insert(std::make_pair(&p,LineaPedido(precio,cant)));

}
void Pedido_Articulo::pedir(Articulo &art, Pedido &p, double precio, unsigned int cant) {
    pedir(p,art,precio,cant);
}

  Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle( Pedido &p) const noexcept {
    auto I= pedido.find(&p);
    if(I== pedido.end()){
        return Pedido_Articulo::ItemsPedido{};
    }
    else{
        return I->second;
    }

 }
  Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo &art) const noexcept {
    auto I= articulo.find(&art);
    if(I==articulo.end()){
        return Pedido_Articulo::Pedidos();
    }else{
        return I->second;
    }


}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream &os) const noexcept {
    double total_importe_pedidos=0;
    for (auto I=pedido.begin();I!=pedido.end();++I){
        total_importe_pedidos= total_importe_pedidos+ I->first->total();
        os<<"Pedido num. "<<I->first->numero()<<std::endl;
        os<<"Cliente: "<<I->first->tarjeta()->titular()->id()<<" \tFecha: "<<I->first->fecha()<<std::endl;
        os<<detalle(*I->first);

    }
    os<<"TOTAL VENTAS\t"<<std::fixed<<std::setprecision(2)<<total_importe_pedidos<<" €"<<std::endl;

}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream &os) const noexcept {
    for(auto I= articulo.begin();I!=articulo.end();++I){
        os<<"Ventas de ["<<I->first->referencia()<<"] \""<<I->first->titulo()<<"\""<<std::endl;
        os<<ventas(*I->first);

    }

}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip){
    double total=0;

    os<<"PVP\tCantidad\tArticulo"<<std::endl;
    os<<std::setfill('=')<<std::setw(70)<<std::endl;
    for(auto I= ip.begin();I !=ip.end();++I){
        total=total+(I->second.precio_venta()*I->second.cantidad());
        os<<std::fixed<<std::setprecision(2)<<I->second.precio_venta()<<" € "<<I->second.cantidad()<<"\t\t["<<I->first->referencia()<<"] \""<<I->first->titulo()<<"\""<<std::endl;

    }
    os<<std::setfill('=')<<std::setw(70)<<std::endl;
    os<<"Total\t"<<std::fixed<<std::setprecision(2)<<total<<" €"<<std::endl;

    return os;

}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p){
    double total=0;
    double cantidad=0;
    os<<"[Pedidos: "<<p.size()<<"]"<<std::endl;
    os<<std::setfill('=')<<std::setw(70)<<std::endl;
    os<<"PVP\tCantidad\tFecha de venta"<<std::endl;
    os<<std::setfill('=')<<std::setw(70)<<std::endl;
    for(auto I= p.begin();I!=p.end();++I){
        total=total+(I->second.precio_venta()*I->second.cantidad());
        cantidad=cantidad+I->second.cantidad();
        os<<std::fixed<<std::setprecision(2)<<I->second.precio_venta()<<" € "<<I->second.cantidad()<<"\t"<<I->first->fecha()<<std::endl;

    }

    os<<std::setfill('=')<<std::setw(70)<<std::endl;
    os<<std::fixed<<std::setprecision(2)<<total<<" €\t"<<cantidad<<std::endl;
    return os;





}














