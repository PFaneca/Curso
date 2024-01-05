//
// Created by ASUS on 05/12/2023.
//
#include "Maior.h"

Regra_Maior::Regra_Maior(Sensor &sensor,double valorComparacao)  : Regra(sensor,"maior_que"),valorComparacao(valorComparacao){}

Regra_Maior::~Regra_Maior() {
    cout << "Destruir r.maior";
}

Regra * Regra_Maior ::duplica() const {
    return new Regra_Maior(*this);
}

string Regra_Maior::getString() const {
    ostringstream  os;
    os << Regra::getString() << " " << valorComparacao << endl;
    return os.str();
}

double Regra_Maior::getvalor() {
    return valorComparacao;
}

bool Regra_Maior::verificar() {
    return getSensor() >= valorComparacao;
}
