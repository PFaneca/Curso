//
// Created by ASUS on 08/11/2023.
//
#include "utils.h"
#include "Sensor.h"




int Sensor::contador=0;


string Sensor::letra() const {
    return "s";
}

int Sensor::getId() const {
    return id;
}

string Sensor::getString()const{
    ostringstream os;
    os << "Sensor " << tipo << id << " da zona "  <<endl;
    return os.str();
}

void Sensor::realizarLeitura() {
    if(propriedade){
        cout << "Sensor " << id << " mede "  << propriedade->gettipo() << " com valor " << propriedade->getvalor() <<propriedade->getunidade() << endl;
    }
    else{
        cout << "Sensor sem propriedade associada." << endl;
    }
}

double Sensor::getvalor_prop() {
    return propriedade->getvalor();
}
double Sensor::setvalor_prop(double novo_valor) {
    propriedade->setvalor(novo_valor);
    return propriedade->getvalor();
}



string Sensor::getunidade() {
    return propriedade->getunidade();
}

string  Sensor::gettipo() const {
    return propriedade->gettipo();
}


