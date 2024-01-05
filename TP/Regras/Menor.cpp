//
// Created by ASUS on 27/12/2023.
//
#include "Menor.h"

Regra_Menor::Regra_Menor(Sensor &sensor, double valor) : Regra(sensor,"igual_a") , valor(valor){}

Regra_Menor::~Regra_Menor() {}

Regra * Regra_Menor ::duplica() const {
    return new Regra_Menor(*this);
}
string Regra_Menor::getString() const {
    ostringstream os;
    os << Regra::getString() << valor << "\n";
    return os.str();
}

bool Regra_Menor::verificar() {
    return getSensor() <= valor;
}