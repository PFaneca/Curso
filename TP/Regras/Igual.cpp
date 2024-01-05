//
// Created by ASUS on 27/12/2023.
//

#include "Igual.h"

Regra_Igual::Regra_Igual(Sensor &sensor, double valor) : Regra(sensor,"igual_a") , valor1(valor){}

Regra_Igual::~Regra_Igual() {}

Regra * Regra_Igual::duplica() const {
    return new Regra_Igual(*this);
}

string Regra_Igual::getString() const {
    ostringstream  os;
    os << Regra::getString() << valor1 << "\n";
    return os.str();
}

bool Regra_Igual::verificar() {
    return getSensor() == valor1;
}