//
// Created by poo on 24/04/23.
//

#include "usuario.hpp"
std::unordered_set< Cadena> Usuario::contenedor_identificadores;

//------------------------------ CLASS CLAVE-----------------------------------
#include <cstdlib> // Para std::rand y std::srand
#include <ctime> // Para std::time
#include <cstring> // Para std::strlen y std::strcmp
#include <random> // Para generación de números aleatorios
#include <string> // Para utilizar std::string en vez de puntero char

Clave::Clave(const char* cad) {
    if (std::strlen(cad) < 5) {
        throw Clave::Incorrecta(CORTA);
    } else {
        const char *cifrado = "zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA9876543210/.";

        // Generar una semilla aleatoria usando std::random_device
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, std::strlen(cifrado) - 1);

        char salt[3]; // Aumentar el tamaño del salt para el formato de crypt
        salt[0] = cifrado[dist(rd)];
        salt[1] = cifrado[dist(rd)];
        salt[2] = '\0'; // Agregar el caracter nulo para el formato de crypt

        char *cadena = crypt(cad, salt); // Almacenar la contraseña cifrada
        if (cadena == nullptr) {
            throw Clave::Incorrecta(ERROR_CRYPT);
        } else {
            contr_cifrada = cadena;
        }
    }
}

bool Clave::verifica(const char* cad) const noexcept {
return !std::strcmp(crypt(cad, contr_cifrada.getter_cad()), contr_cifrada.getter_cad());
}





//------------------------------------CLASE USUARIO-------------------------------
Usuario::Usuario(const Cadena &i, const Cadena &nom, const Cadena &ap, const Cadena &d, const Clave &c):_identificador(i),_nombre(nom),_apellidos(ap),_direccion(d),_constrasena(c)
{
    auto res= contenedor_identificadores.insert(_identificador);
    if (res.second== false){
        throw Id_duplicado(_identificador);
    }

}
Usuario::~Usuario() {
    for( auto i= _tarjetas.begin();i!=_tarjetas.end();i++){
        (i->second)->anula_titular();
    }
    contenedor_identificadores.erase(_identificador);

}
void Usuario::es_titular_de(Tarjeta &t) {
    if(t.titular()==this){
        _tarjetas.insert(std::make_pair(t.numero(),&t));
    }


}
void Usuario::no_es_titular_de(Tarjeta &t) {
        _tarjetas.erase(t.numero());
        t.anula_titular();
        t.activa(true);
}
void Usuario::compra(const Articulo &art, unsigned int cant) {
    auto comprobar= _articulos.find(const_cast<Articulo*>(&art));
    if (comprobar==_articulos.end()){
        if (cant>0){
            _articulos.insert(std::make_pair(const_cast<Articulo*>(&art),cant));

        }
    }else{
        if (cant>0){
            comprobar->second=cant;
        }else{
            _articulos.erase(comprobar);
        }
    }



}
void Usuario::vaciar_carro() {
        _articulos.clear();


}
std::ostream& operator <<(std::ostream& os, const Usuario& U){
    os<<U.id()<<" ["<<U._constrasena.clave()<<"] "<<U.nombre()<<" "<<U.apellidos()<<std::endl
      <<U.direccion()<<std::endl<<"Tarjetas:"<<std::endl;

    for(auto i = U.tarjetas().begin(); i != U.tarjetas().end(); i++)
    {
        os << *(i->second) << std::endl ;
    }

    return os;

}
void mostrar_carro(std::ostream& os, const Usuario& U){
    os<<"Carrito de compra de "<<U.id()<<" [Artículos: "<<U.n_articulos()<<"]"<<std::endl<<
      " Cant. Artículo"<<std::endl<<"==========================================================="<<std::endl;
    for(auto i = U.compra().begin(); i != U.compra().end(); i++)
    {
        os<<"	"<< i->second<<"	" <<"["<<i->first->referencia()<<"]"<<" \""<<i->first->titulo()<<"\", "<<i->first->f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<i->first->precio()<<" €"<<std::endl;
    }



}


