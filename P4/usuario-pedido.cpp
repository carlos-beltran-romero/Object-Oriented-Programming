//
// Created by Carlitoxere on 03/08/2023.
//

#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario &u, Pedido &p) {
    map_u[&u].insert(&p);
    map_p.insert(std::make_pair(&p,&u));

}
void Usuario_Pedido::asocia(Pedido &p, Usuario &u) {
    asocia(u,p);
}
 Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario &u) const noexcept {
    auto I= map_u.find(&u);
    if(I==map_u.end()){
        return Usuario_Pedido::Pedidos();
    }
    else{
        return I->second;
    }

}
   Usuario* Usuario_Pedido::cliente(Pedido &p) const noexcept {
    return (map_p.find(&p)->second);


}
