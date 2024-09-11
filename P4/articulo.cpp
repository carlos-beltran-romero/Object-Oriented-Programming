

#include "articulo.hpp"
using namespace std;
Articulo::Articulo(const std::set<Autor*>& aut,Cadena cod, Cadena t, Fecha f_pub, double p) :A(aut), referencia_(cod), titulo_(t), f_publi_(f_pub),precio_(p){
    if (aut.empty()){
        throw Autores_vacios();
    }


}
ostream& operator <<(ostream& onto, const Articulo& art){



    onto<<"["<<art.referencia()<<"]"<<" \""<<art.titulo()<<"\", de ";
    auto I= art.autores().begin();
    onto<<(*I)->apellidos();
    ++I;
    while (I!=art.autores().end()){
        onto<<", "<<(*I)->apellidos();
        I++;

    }
    onto<<". "<<art.f_publi().anno()<<". "<<fixed<<setprecision(2)<<art.precio()<<" €"<<"\n\t";
    art.impresion_especifica(onto);
    return onto;
}

void Libro::impresion_especifica(std::ostream& onto) const {
    onto<<n_pag_<<" págs., "<<stock_<<" unidades.";

}
void Revista::impresion_especifica(std::ostream& onto ) const {
    onto<<"Número: "<<numero_<<", Periodicidad: "<<periodicidad_<<" días.\n\t";
    onto<<"Próximo número a partir de: "<<f_publi()+periodicidad_<<".";

}
void LibroDigital::impresion_especifica(std::ostream& onto) const {
    onto<<"A la venta hasta el "<<f_expir_<<".";

}





