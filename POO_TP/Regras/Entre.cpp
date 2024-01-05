//
// Created by ASUS on 05/12/2023.
//

#include "Entre.h"

Regra_entre::Regra_entre(Sensor &sensor,double valor1, double valor2) : Regra(sensor,"entre") ,valor1(valor1),valor2(valor2) {}


Regra* Regra_entre::duplica() const {
    return new Regra_entre(*this);
}

Regra_entre::~Regra_entre() {
    cout << "A destruir r.entre";
}

string Regra_entre::getString() const {
    ostringstream  os;
    os << Regra::getString() << valor1 << " e " << valor2 << "\n";
    return os.str();
}

bool Regra_entre::verificar() {
    return getSensor() >= valor1 && getSensor() <= valor2;
}
