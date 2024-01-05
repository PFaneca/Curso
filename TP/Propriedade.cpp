//
// Created by ASUS on 01/11/2023.
//
#include "utils.h"
#include "Propriedade.h"

Propriedade::Propriedade(string nome, double val, double val_min, double val_max,string unidade_) {
    tipo=nome;
    unidade=unidade_;
    valor=val;
    valor_min=val_min;
    valor_max=val_max;
    if(val >= val_min && val <= val_max){
        valor = val;
    }
    else{
        throw std::out_of_range("Valor inicial fora do intervalo permitido.");
    }

}

Propriedade::Propriedade(const Propriedade &outro) {
    *this=outro;
}

string Propriedade::gettipo() const {
    return tipo;
}

string Propriedade::getunidade()const{
    return unidade;
}

double Propriedade::getvalor() const {
    return valor;
}

bool Propriedade::setvalor(double novovalor) {
    if (novovalor >= valor_min && novovalor <= valor_max) {
        valor = novovalor;
        return true;  // Indica que o valor foi definido com sucesso
    } else {
        std::cout << "Valor fora do intervalo permitido.\n";
        return false;  // Indica que o valor não foi definido
    }
}
void Propriedade::addvalor(double valorAdicionar) {
    valor +=valorAdicionar;
}

void Propriedade::subvalor(double valorSubtrair) {
    valor -= valorSubtrair;
}

string Propriedade::getString() const {
    ostringstream os;
    os << "(" << tipo << "," << valor <<  unidade <<")\n";
    return os.str();
}