
#include "fecha.hpp"
#include <cstdio>
#include <chrono>
#include <ctime>
// CONSTRUCTORES

Fecha::Fecha(int dia, int mes, int annio):d(dia),m(mes),a(annio){
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* now = std::localtime(&t);
    if(d==0){
        d=now->tm_mday;
    }
    if(m==0){
        m=now->tm_mon+1;

    }
    if(a==0){
        a=now->tm_year+1900;
    }

    comprobarfecha();
}
Fecha::Fecha(const char *fech) {
    int num=sscanf(fech, "%d/%d/%d", &d, &m, &a);
    if(num!=3){
        throw Invalida("Fecha Incorrecta");
    }
    else{
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm* now = std::localtime(&t);
        if(d==0){
            d=now->tm_mday;
        }
        if(m==0){
            m=now->tm_mon+1;

        }
        if(a==0){
            a=now->tm_year+1900;
        }else while(a>9999) a/=10;
        comprobarfecha();


    }
}
// COMPROBAR FECHA

void Fecha::comprobarfecha()const {

    if(d < 1 || m < 1 || m > 12 || a < AnnoMinimo ||a>AnnoMaximo||d > 31 ||
       ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) || //MESES CON 30 DIAS
       (m == 2 && (d > 29 || (d == 29 && (a % 4 != 0 || (a % 100 == 0 && a % 400 != 0))))))// MES FEBRERO >29 O AÑO BISIESTO
    {
        throw Invalida("Fecha Invalida");

    }
}

//CONVERSION DE FECHA A CONST CHAR*
    const char* Fecha::cadena() const {
    std::locale::global(std::locale("es_ES.utf8"));
    static char cad2[100];
    std::time_t t= std::time(nullptr);
    std::tm* fi= std::localtime(&t);

    fi->tm_mday=d;
    fi->tm_mon=m-1;
    fi->tm_year=a-1900;
    mktime(fi);
    strftime(cad2,100,"%A %e de %B de %Y",fi);
    return cad2;

}

//OBSERVADORES
inline int Fecha::anno() const noexcept{return a;}
inline int Fecha::mes() const noexcept {return m;}
inline int Fecha::dia() const noexcept{return d;}

//OPERADORES ARITMÉTICOS
Fecha& Fecha::operator+=(int num) {
    //SUMAR DIA+ NORMALIZAR FECHA
    std::tm f{};
    f.tm_mday=d+num;
    f.tm_mon=m-1;
    f.tm_year=a-1900;
    std::mktime(&f);
    d= f.tm_mday;
    m=f.tm_mon+1;
    a=f.tm_year+1900;
    comprobarfecha();
    return *this;

}
Fecha& Fecha::operator-=(int num) {
    *this+= -num;
    return *this;

}
Fecha& Fecha::operator++() {
    *this+=1;
    return *this;
}
Fecha Fecha::operator++(int num)  {
    Fecha f=*this;
    *this+=1;
    return f;

}
Fecha& Fecha::operator--() {
    *this+=-1;
    return *this;


}
Fecha Fecha::operator--(int) {
    Fecha f=*this;
    *this+=-1;
    return f;


}
Fecha Fecha::operator+(int num) const {
    Fecha f= *this;
    f+=num;
    return f;

}
Fecha Fecha::operator-(int num) const {
    Fecha f= *this;
    f+=-num;
    return f;
}

// OPERADORES DE COMPARACION
bool operator ==(const Fecha& A,const Fecha& B){
    bool escape;
    if( A.dia()==B.dia()&&A.mes()==B.mes()&&A.anno()==B.anno()){
        escape=true;

    }else{
        escape=false;
    }
    return escape;
}

bool operator <(const Fecha& A,const Fecha& B){
    bool escape=false;
    if(A.anno()<B.anno()){
        escape= true;
    }else if(A.anno()==B.anno()&& A.mes()<B.mes()){
        escape=true;
    }else if(A.anno()==B.anno()&&A.mes()==B.mes()&&A.dia()<B.dia()){
        escape=true;
    }
    return escape;

}
bool operator >(const Fecha& A,const Fecha& B){
    return (B<A);
}
bool operator >=(const Fecha& A,const Fecha& B){
    return !(A<B);
}
bool operator <=(const Fecha& A,const Fecha& B){
    return !(B<A);
}
bool operator !=(const Fecha& A,const Fecha& B){
    return !(A==B);
}

// OPERADOR DE EXTRACCION
std::istream& operator >>(std::istream&  into, Fecha& f){
     char cadena[11];
    into.getline(cadena,11);
    try{
        Fecha f3 {cadena};
    }catch ( const Fecha::Invalida ex){
        into.setstate(std::ios_base::failbit);
        throw ex;

    }
     Fecha f3{cadena};
    f=f3;
    return into;
}
//OPERADOR DE INSERCION

std::ostream& operator <<(std::ostream& salida,const Fecha& f){
    salida<<f.cadena();
    return salida;
}








