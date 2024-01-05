//
// Created by ASUS on 29/12/2023.
//
#include "Fora.h"

Regra_Fora::Regra_Fora(Sensor &sensor, double valor1, double valor2) : Regra(sensor,"fora"), valor1(valor1),valor2(valor2) {}

Regra_Fora::~Regra_Fora(){}


Regra *Regra_Fora::duplica() const {
    return new Regra_Fora(*this);
}

string Regra_Fora::getString() const {
    ostringstream os;
    os << Regra::getString() << valor1 << " e " << valor2 << "\n";
    return os.str();
}

bool Regra_Fora::verificar() {
    return getSensor() < valor1 || getSensor() > valor2;
}