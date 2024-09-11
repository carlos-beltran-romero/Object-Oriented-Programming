//
// Created by Carlitoxere on 03/08/2023.
//

#ifndef P3_USUARIO_PEDIDO_H
#define P3_USUARIO_PEDIDO_H

#include <ostream>
#include <set>
#include <map>
class Usuario;
class Pedido;


class Usuario_Pedido {
public:
    typedef std::set<Pedido*> Pedidos;
    // ENLAZA
    void asocia(Usuario& u, Pedido& p);
    void asocia(Pedido& p, Usuario& u);

    //DEVUELVE
     Pedidos pedidos(Usuario& u)const noexcept;
     Usuario* cliente(Pedido& p)const noexcept;


private:
    //SINONIMO
    typedef std::map<Usuario*,Pedidos> U;
    typedef std::map<Pedido*,Usuario*> P;
    U map_u;
    P map_p;
};


#endif //P3_USUARIO_PEDIDO_H



