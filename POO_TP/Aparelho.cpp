//
// Created by ASUS on 14/11/2023.
//
#include "Aparelho.h"

using namespace std;
using namespace term;

Aparelho::Aparelho(string tipo, string nome_) : tipo(tipo),nome(nome_){
    comando="desligado";
    ligado= false;
    id=++contador;}


int Aparelho::contador=0;

Aparelho::~Aparelho() {}

string Aparelho::getletra(){
    return letra;
}

string Aparelho::gettipo() {
    return tipo;
}


string Aparelho::getnome()const{
    return nome;
}

string Aparelho::getComando()const{
    return comando;
}

void Aparelho::AtualizarComando(const std::string& novoComando, Window& infos) {
    comando = novoComando;
    infos << set_color(0) << "Comando do aparelho " <<getletra() <<getId() << " atualizado para: " << comando << "\n";
    if(novoComando == "liga" && letra =="a"){
        letra=letraMaiuscula;

    }
}



int Aparelho::getId() const {
    return id;
}

string Aparelho::getString() const {
    ostringstream os;
    os<<"Aparelho " << tipo << id<<"->"<<letra << "," << nome << endl ;
    return os.str();
}





void Aparelho::ligar() {

    if(ligado)return;
    ligado = true;
    instante_ligado=0;
   // this->instanteLigado() = Zona->getInstante;
   aoLigar();
}

void Aparelho::desligar() {
    ligado= true;
    if(!ligado)return;
    ligado = false;
    aoDesligar();
}

void Aparelho::aoLigar() {}

void Aparelho::aoDesligar() {}

Sensor* Aparelho::encontrarsensorProp(const std::string& nomePropriedade) {
    for (auto sensor : sensores) {
        if (sensor->gettipo() == nomePropriedade) {
            return sensor;
        }
    }
    return nullptr;  // Retorna nullptr se não encontrar o sensor com a propriedade desejada
}


//const std::vector<Propriedade*>Aparelho::props() {
//    return propriedades;
//}

void Aparelho::AdicionarPropriedade(Propriedade &prop) {
    propriedades.push_back(&prop);
}

void Aparelho::exibirprop(Window &infos) {
    infos << "Propriedades do Aparelho:\n";
    for (const auto& propriedade : propriedades) {
        // Realize a operação desejada com cada propriedade (por exemplo, exibição)
        infos << " - " << propriedade->getString() << "\n";
    }
}


Propriedade* Aparelho::getPropriedade(const std::string& tipo) {
    for (Propriedade *prop : propriedades) {
        if (prop->gettipo() == tipo) {
            return prop;
        }
    }
    return nullptr; // Retorna nullptr se a propriedade não for encontrada
}
int Aparelho::getInstanteAtual() {

}



int Aparelho::getInstanteLigado() {}