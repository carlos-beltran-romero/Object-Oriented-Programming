//
// Created by poo on 23/04/23.
//

#ifndef P2_TARJETA_H
#define P2_TARJETA_H

#include <set>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <cstring>
class Usuario;




//--------------CLASS NUMERO---------------------

class Numero{
public:
    //CONSTRUCTOR
    Numero( const Cadena& num);

    // ENUMERACION
    enum Razon{LONGITUD, DIGITOS,NO_VALIDO};

    //CLASS INCORRECTO
    class Incorrecto{
    public:
        Incorrecto(Numero::Razon r):reason(r){}
        Numero::Razon razon()const noexcept{return reason;}


    private:
        Numero::Razon reason;
    };
    // OPERATOR <
     friend bool operator <(const Numero& num1, const Numero& num2);


    // OPERADOR DE CONVERSION A CADENA DE CARACTERES
    operator const char*()const{return numero.getter_cad();}

private:
    Cadena numero;
};


//--------------CLASS TARJETA---------------------


class Tarjeta {
public:
    enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
    //CONSTRUCTOR
    Tarjeta(const Numero& n,Usuario& u,const Fecha& f);
    Tarjeta(const Tarjeta& t2)=delete;
    Tarjeta& operator=(const Tarjeta& t2)=delete;
    ~Tarjeta();

    //OBSERVADORES
    const Numero& numero() const noexcept{return num_tarjeta;}
    Usuario* titular() const noexcept{return  _titular;}
    const Fecha& caducidad() const noexcept{return _caducidad;}
    bool activa() const noexcept{return tarjeta_activa;}
    Tipo tipo() const noexcept;

    //METODO MODIFICADOR ACTIVA/ NO ACTIVA
    bool activa(bool nuevo_estado){ tarjeta_activa=nuevo_estado; return tarjeta_activa;}




    //CLASS CADUCADA
    class Caducada{
    public:
        Caducada(const Fecha& caducada): caducada(caducada){}
        const Fecha& cuando()const noexcept{ return caducada;}
    private:
        Fecha caducada;
    };

    // CLASS NUM_DUPICADO
    class Num_duplicado{
    public:
        Num_duplicado(const Numero& num): n(num){}
        const Numero& que()const noexcept{return n;}
    private:
        Numero n;
    };

    //CLASS DESACTIVADA
    class Desactivada{
    };




private:
    const Numero num_tarjeta;
    const Fecha _caducidad;
    bool tarjeta_activa;
     Usuario*  const _titular;
    static std::set<Numero> tarjetas;

    // METODO MODIFICADOR ANULA TITULAR
    friend class Usuario;
    void anula_titular();


};

std::ostream& operator <<(std::ostream& os,const Tarjeta& t);
std:: ostream& operator <<(std::ostream& onto, const Tarjeta::Tipo& tip);
bool operator <(const Tarjeta& t1, const Tarjeta& t2);


#endif //P2_TARJETA_H
