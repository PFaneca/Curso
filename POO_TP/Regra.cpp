//
// Created by ASUS on 15/11/2023.
//

#include "Regra.h"

Regra::Regra(Sensor &sensor,string descricao) : sensorassociado(&sensor), descricao(descricao) {id=++contador;}

int Regra::contador=0;

Regra::~Regra() {
    cout << "A destruir regra";
}

Regra *Regra::duplica() const {

}

int Regra::getId() const {
    return id;
}
string Regra::gettipo() const {
    return tipo;
}

string Regra:: getDescricao()const{
    return descricao;
}



string Regra:: getString()const{
    ostringstream os;
    os << "Regra " << tipo << id << ":" << descricao;
    return os.str();
}

Sensor *Regra::getSensorAssociado() const {
    return sensorassociado;
}

double Regra::getSensor() {
    return sensorassociado->getvalor_prop();
}

bool Regra::verificar() {}

bool Regra::contemSensor(int id_sensor) const {
    return sensorassociado->getId()==id_sensor;
}