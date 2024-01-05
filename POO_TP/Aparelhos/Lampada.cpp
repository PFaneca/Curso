//
// Created by ASUS on 31/12/2023.
//
#include "Lampada.h"

Lampada::Lampada() : Aparelho("l","lampada" ){

}

Lampada::~Lampada() {}

string Lampada::getString() const {
    return Aparelho::getString();
}

void Lampada::aoLigar() {
    getPropriedade("Luz")->addvalor(900);
}

void Lampada::aoDesligar() {
    getPropriedade("Luz")->subvalor(900);
}