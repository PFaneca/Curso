//
// Created by ASUS on 08/12/2023.
//
#include "Aquecedor.h"


Aquecedor::Aquecedor() : Aparelho("a","aquecedor") {

}

Aquecedor::~Aquecedor()  {}

string Aquecedor::getString() const {
    return Aparelho::getString();
}



//void Aquecedor::ligar() {


//}

void Aquecedor::aoLigar() {

    if (getInstanteAtual() == ultimoaumentoTemperatura + 3) {
        ultimoaumentoTemperatura = getInstanteAtual();
        Propriedade *temperatura = getPropriedade("Temperatura");

        if (temperatura->getvalor() < 50) {
            temperatura->addvalor(1);
        }
    }
    getPropriedade("Som")->addvalor(5);

}
void Aquecedor::aoDesligar() {

    getPropriedade("Som")->subvalor(5);
}


