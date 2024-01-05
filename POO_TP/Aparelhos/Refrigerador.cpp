//
// Created by ASUS on 31/12/2023.
//
#include "Refrigerador.h"

Refrigerador::Refrigerador() : Aparelho("r","refrigerador") {

}

Refrigerador::~Refrigerador(){

}

string Refrigerador::getString() const {
    return Aparelho::getString();
}

void Refrigerador::aoLigar() {
    if(getInstanteLigado() == getInstanteAtual() + 3){
        Propriedade * temperatura = getPropriedade("Temperatura");
            temperatura->subvalor(1);
    }
    if(getInstanteLigado()==1){
        getPropriedade("Som")->addvalor(20);
    }

}

void Refrigerador::aoDesligar() {
    getPropriedade("Som")->subvalor(20);
}