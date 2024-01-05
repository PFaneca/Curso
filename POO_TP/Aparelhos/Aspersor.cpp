//
// Created by ASUS on 31/12/2023.
//
#include "Aspersor.h"

Aspersor::Aspersor() : Aparelho("s","aspersor"){

}

Aspersor::~Aspersor() {}

string Aspersor::getString() const {
    return Aparelho::getString();
}

void Aspersor::aoLigar() {
    if(getInstanteLigado()==1){
        Propriedade * humidade= getPropriedade("Humidade");
        int novovalor=humidade->getvalor() * 1.5;
        humidade->setvalor(min(novovalor,75));

    }
}

void Aspersor::aoDesligar() {
    getPropriedade("Vibracao")->subvalor(100);
}