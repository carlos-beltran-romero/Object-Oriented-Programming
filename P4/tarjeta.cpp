//
// Created by poo on 23/04/23.
//

#include "tarjeta.hpp"
bool luhn(const Cadena& num);
std::set<Numero> Tarjeta::tarjetas;

class EsBlanco{
public:
    bool operator()(char c){return isspace(c);}
};

Cadena eliminar_esp(const Cadena& cad)
{
    Cadena aux (cad) ;

    std::remove_if(aux.begin(),aux.end()+1,[](char x){return isspace(x);});

    return Cadena(aux.getter_cad()) ;
}
class EsDigito: public std::unary_function<char,bool>{
public:
    bool operator()(char c) const {return isdigit(c);}
};



//------------------CLASE NUMERO--------------------
Numero::Numero(const Cadena& n):numero(eliminar_esp(n))
{

    if(numero.length() < 13 || numero.length() == 0 || numero.length() > 19)
    {
        throw Incorrecto(Razon::LONGITUD) ;
    }
    std::unary_negate<EsDigito> NoEsDigito((EsDigito()));
    if(find_if(numero.begin(), numero.end(), NoEsDigito) != numero.end())
    {
        throw Incorrecto(Razon::DIGITOS);
    }

    if(!luhn(numero))
    {
        throw Incorrecto(Razon::NO_VALIDO);
    }
}
bool operator <(const Numero& num1, const Numero& num2){
    return num1.numero<num2.numero;
}

// ----------------------CLASE TARJETA--------------------------
Tarjeta::Tarjeta(const Numero &n, Usuario &u, const Fecha &f): num_tarjeta(n),_caducidad(f), tarjeta_activa(true),_titular(&u){
    Fecha actual;
    if(actual>_caducidad){
        throw Caducada(_caducidad);
    }else if( tarjetas.insert(num_tarjeta).second==false){
        throw Num_duplicado (num_tarjeta);
    }else{
        _titular->es_titular_de(*this);

    }

}
Tarjeta::~Tarjeta() {
    if(_titular){
        _titular->no_es_titular_de(*this);
    }
    tarjetas.erase(num_tarjeta);

}
Tarjeta::Tipo Tarjeta::tipo() const noexcept {
    Tipo devolver;

    if (num_tarjeta[0]=='3' &&(num_tarjeta[1]=='7'||num_tarjeta[1]=='4')){ //num_tarjeta se convierte en const char*
        devolver= Tipo::AmericanExpress;

    }else if(num_tarjeta[0]=='3' &&!(num_tarjeta[1]=='7'||num_tarjeta[1]=='4')){
        devolver= Tipo::JCB;
    }else if(num_tarjeta[0]=='4'){
        devolver=Tipo::VISA;
    }else if(num_tarjeta[0]=='5'){
        devolver=Tipo::Mastercard;
    }else if(num_tarjeta[0]=='6'){
        devolver=Tipo::Maestro;
    }else{
        devolver=Tipo::Otro;
    }
    return devolver;



}
void Tarjeta::anula_titular() {
    tarjeta_activa=false;
    const_cast<Usuario*&>(_titular) =nullptr;

}

std::ostream& operator <<(std::ostream& os,const Tarjeta::Tipo& t){
        switch(t){
            case Tarjeta::VISA: os << "VISA"; break;
            case Tarjeta::Mastercard: os << "Mastercard"; break;
            case Tarjeta::Maestro: os << "Maestro"; break;
            case Tarjeta::JCB: os << "JCB"; break;
            case Tarjeta::AmericanExpress: os << "American Express"; break;
            case Tarjeta::Otro: os<<"Tipo indeterminado";      break;
            default: os << "Error";
        }
        return os;

}
std:: ostream& operator <<(std::ostream& onto,const Tarjeta& tarj){
    onto<<tarj.tipo()<<std::endl;
    onto<<tarj.numero()<<std::endl;
    Cadena aux= tarj.titular()->nombre()+ " "+tarj.titular()->apellidos();
    for (auto& c: aux){
        if(islower(c)){
            c= toupper(c);
        }

    }
    onto<<aux<<std::endl;
    onto <<std::right<<"Caduca: "<<std::setfill('0')<<std::setw(2)<<(tarj.caducidad().mes())<<"/"<<std::setw(2)<<(tarj.caducidad().anno()%100)<<std::endl;

    return onto;


}
bool operator <(const Tarjeta& t1, const Tarjeta& t2){
    return t1.numero()<t2.numero();

}
