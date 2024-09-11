//
// Created by poo on 21/02/23.
//

#include "cadena.hpp"
using namespace std;

//CONSTRUCTORES
Cadena::Cadena(size_t tam,char c):s_(new char[tam+1]),tam_(tam) {

    for(size_t i=0;i<tam;i++){
        s_[i]=c;
    }
    s_[tam]='\0';


}
Cadena::Cadena(const Cadena &cad):s_{new char[cad.tam_+1]},tam_{cad.tam_} {
    strcpy(s_,cad.s_);

}
Cadena::Cadena(const char *c):s_(new char[(strlen(c)+1)]),tam_(strlen(c)) {
    strcpy(s_,c);
}
Cadena::Cadena(Cadena&& cad):s_(cad.s_), tam_(cad.tam_) {
    cad.s_= new char[1];
    cad.s_[0]='\0';
    cad.tam_=0;
}

//OPERADORES ASIGNACION
Cadena& Cadena::operator=(const Cadena &cad) {
    if(*this!=cad){
        delete[] s_;
        tam_= cad.tam_;
        s_= new char[tam_+1];
        strcpy(s_,cad.s_);
    }
    return *this;
}
Cadena& Cadena::operator=(const char *cad) {
    if(strcmp(s_,cad)!=0){
        tam_= strlen(cad);
        delete[] s_;
        s_=new char[tam_+1];
        strcpy(s_,cad);

    }
    return *this;
}

// ASIGNACION MOVIMIENTO
Cadena& Cadena::operator=(Cadena&& cad) {
    if(this!= &cad){
        delete[] s_;
        s_=cad.s_;
        tam_=cad.tam_;
        cad.tam_=0;
        cad.s_= new char [1];
        cad.s_[0]='\0';



    }
    return *this;
}




//OPERADORES ARITMETICOS
Cadena& Cadena::operator+=(const Cadena &cad) {
    Cadena aux(*this) ;
    tam_ += cad.tam_ ;
    delete[] s_ ;
    s_ = new char [tam_ + 1] ;

    strcpy(s_,aux.s_) ;
    strcat(s_,cad.s_) ;


    return *this ;

}
// METODOS
char& Cadena::operator[](size_t indice)noexcept {
    return s_[indice];
}
const char& Cadena::operator[](size_t indice) const noexcept {
    return s_[indice];
}
const char& Cadena::at(size_t indice) const {
    if (indice>=0&&indice<tam_){
        return s_[indice];
    }else{
        throw std::out_of_range("Fuera de rango");
    }
}
char& Cadena::at(size_t indice) {
    if (indice>=0&&indice<tam_){
        return s_[indice];
    }else{
        throw std::out_of_range("Indice fuera de rango");
    }

}
Cadena Cadena::substr(size_t indice, size_t tamanio) const {
    if (indice>tam_||indice+tamanio>tam_||indice<0||tamanio<0||tamanio>tam_){
        throw std::out_of_range("Fuera de rango");
    }else{
        char *c= new char [tamanio+1];

        size_t cont=0;


        for(size_t i=indice;i<indice+tamanio;i++){
            c[cont]=s_[i];
            cont++;

        }
        c[tamanio]='\0';
        Cadena cad(c);
        delete[] c;
        return cad;
    }

}
// DESTRUCTOR
Cadena::~Cadena() {
    delete[]s_;
    tam_=0;
}
Cadena operator +(const Cadena& A,const Cadena& B){
    Cadena cad(A);
    cad+=B;
    return cad;
}
// OPERADORES DE COMPARACION
bool operator ==(const Cadena& A,const Cadena& B){
    return strcmp(A.getter_cad(),B.getter_cad())==0;
}
bool operator <(const Cadena& A,const Cadena& B){
    return strcmp(A.getter_cad(),B.getter_cad())<0;
}
bool operator >(const Cadena& A,const Cadena& B){
    return B<A;
}
bool operator !=(const Cadena& A,const Cadena& B){
    return !(A==B);
}
bool operator <=(const Cadena& A,const Cadena& B){
    return (A<B || A==B);
}
bool operator >=(const Cadena& A,const Cadena& B){
    return (A>B || A==B);
}

// OPERADOR DE EXTRACCIÓN
std::istream& operator >>(std::istream&  into,Cadena& c) {
    char cadenita[33];
    into.width(33); // Se va a leer como maximo 33 carcateres de la entrada de flujo

   // Si el caracter actual de la entrada es un caracter en blanco se saca del flujo
    while (std::isspace(into.peek()) && into.peek() != EOF) {
        into.get();
    }

    //SI despues de quitar los espacios en blancos se tiene que la entrada esta vacia, se crea una cadena vacia
    if (into.peek() == EOF) {
        c = "";
        return into;
    }

    into >> cadenita;
    Cadena cad(cadenita);
    c = cad;
    return into;
}
//OPERADOR DE INSERCION
std::ostream& operator <<(std::ostream& cout,const Cadena& c){
    cout<<c.getter_cad();
    return cout;
}

