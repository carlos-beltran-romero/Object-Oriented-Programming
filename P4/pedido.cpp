
#include "pedido.hpp"

int Pedido::N_pedidos=0;

Pedido::Pedido( Usuario_Pedido& UP, Pedido_Articulo &PA, Usuario &U, const Tarjeta& t,
               const Fecha &f):num_(N_pedidos+1), tarjeta_(&t), fecha_(f),total_(0){

    if(U.n_articulos()==0) throw Pedido::Vacio(U);
    if(t.titular()!=&U) throw Pedido::Impostor(U);
    auto carrito=U.compra();


    if(t.caducidad()<fecha_) throw Tarjeta::Caducada(t.caducidad());
    if(!t.activa()) throw Tarjeta::Desactivada();

    for(auto& i:carrito){
        if(ArticuloAlmacenable* A=dynamic_cast<ArticuloAlmacenable*>(i.first)){

            if(i.second > A->stock())
            {
                Articulo *art=i.first;
                U.vaciar_carro();
                throw Pedido::SinStock(*art);
            }
        }
        else{
            if(LibroDigital* L=dynamic_cast<LibroDigital*>(i.first)){
                if(L->f_expir()<f){
                    U.compra().erase(L);
                    i.first->precio()=0;
                }
            }
        }
    }
    if(U.compra().empty()){
        throw Pedido::Vacio(U);
    }

    UP.asocia(U,*this);

    for(auto& i:carrito){
        total_+=i.first->precio() * i.second;

        if(ArticuloAlmacenable* aa=dynamic_cast<ArticuloAlmacenable*>(i.first)) aa->stock()-=i.second;
        PA.pedir(*this,*i.first,i.first->precio(),i.second);
    }
    U.vaciar_carro();
    N_pedidos++;




}





std::ostream& operator <<(std::ostream& os, const Pedido& p){
    os<<"Núm. pedido: "<<p.numero()<<std::endl;
    os<<"Fecha:\t"<<p.fecha()<<std::endl;
    os<<"Pagado con:\t"<<p.tarjeta()->tipo()<<" n.º: "<<p.tarjeta()->numero()<<std::endl;
    os<<"Importe:\t"<<std::fixed<<std::setprecision(2)<<p.total()<<" €"<<std::endl;
    return os;

}





