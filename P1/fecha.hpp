//
// Created by poo on 13/02/23.
//


#ifndef P0_FECHA_HPP
#define P0_FECHA_HPP
#include <iostream>


class Fecha {
public:

    //CONSTRUCTORES

    explicit Fecha(int dia=0, int mes=0, int annio=0 );
    Fecha(const char* fech );



    Fecha& operator ++();//PreIncremento
    Fecha operator ++(int) ; //PostIncremento
    Fecha& operator --();// PreDecremento
    Fecha operator --(int);//PostDecremento
    Fecha operator +(int num) const;
    Fecha operator -(int num) const;
    Fecha& operator -=(int num)  ;
    Fecha& operator +=(int num) ;

    //OBSERVADORES

    int dia()const noexcept;
    int mes()const noexcept;
    int anno()const noexcept;

//CONVERSION DE FECHA A CONST CHAR*
      const char* cadena ()const;

    //CLASE INVALIDA
    class Invalida{
    public:
        Invalida(const char* fallo_): fallo(fallo_){};
        const char* por_que()const noexcept {return fallo;};
    private:
        const char* fallo;

    };
    static const int AnnoMinimo=1902;
    static const int AnnoMaximo=2037;

private:
    int d,m,a;
    void comprobarfecha()const ;


};
bool operator <(const Fecha& A,const Fecha& B);
bool operator <=(const Fecha& A,const Fecha& B);
bool operator ==(const Fecha& A,const Fecha& B);
bool operator >(const Fecha& A,const Fecha& B);
bool operator >=(const Fecha& A,const Fecha& B);
bool operator !=(const Fecha& A,const Fecha& B);
// OPERADOR DE EXTRACCIÓN E INSERCIÓN
std::istream& operator >>(std::istream&  into,Fecha& f);
std::ostream& operator <<(std::ostream& cout,const Fecha& f);


#endif //P0_FECHA_HPP