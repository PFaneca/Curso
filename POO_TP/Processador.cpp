//
// Created by ASUS on 15/11/2023.
//


#include "Processador.h"
#include "vector"
using namespace std;
using namespace term;



Processador::Processador(const Processador &outro) {
    //id=++contador;
    //for(Regra *p : outro.regras)
      //  regras.emplace_back(new Regra(*p));
        //id=outro.id;
        *this = outro;
}

Processador & Processador::operator=(const Processador &orig) {
    if(this == & orig){
        return *this;
    }
    for(int i=0;i<regras.size();i++){
        delete regras[i];
    }
    regras.clear();
    for(int i=0;i<orig.regras.size();i++){
        Regra *p=orig.regras[i]->duplica();
        regras.push_back(p);
    }
    return  *this;
}

int Processador::contador=0;

Processador::~Processador() {
    for(Regra *regra : regras){
        delete regra;
    }
}

int Processador::getId() const {
    return id;
}

string Processador::getletra() const {
    return letra;
}

string Processador::getString() const {
    ostringstream os;
    os << "Processador " <<letra << id << "\nRegras associadas:\n";
    for(const auto &regra:regras){
        os << regra->getString() << '\n';
    }
    return os.str();
}

string Processador::getComando() {
    return comandoProc;
}

void Processador::setComando(const string &novoComando){
    comandoProc=novoComando;
}


void Processador::AdicionarRegra(Regra* regra) {
    regras.emplace_back(regra);
}

bool Processador::RemoverRegra(int idregra) {
    for(auto it=regras.begin();it!=regras.end();it++){
        if((*it)->getId()==idregra){
            delete *it;
            regras.erase(it);
            return true;
        }
    }

    return  false;
}


void Processador::ListarRegras(Window &infos) {
    for (auto regra : regras) {
        infos << set_color(0)<< "Nome da regra: " << regra->getDescricao() << " (id: r" << regra->getId() << ")";
        Sensor *sensorAsssociado = regra->getSensorAssociado();
        if(sensorAsssociado != nullptr){
            infos << set_color(0)<< "Sensor associado: " << sensorAsssociado->gettipo() << " (id: s" << sensorAsssociado->getId() << ")\n";
        }
        else{
            infos << set_color(4)<< "Sem sensor associado\n";
        }
        infos << "\n";
    }

}

int Processador::contaRegras() {
    return regras.size();
}


Aparelho *Processador::getAparelhoAssociado() const {
    return aparelho;
}

//const std::vector<Aparelho*> &Processador::  getAparelhosAssociados() const {
//    return aparelhos;
//}



void Processador::associarAparelho(Aparelho* novoAparelho) {
   aparelho=novoAparelho;
}


const std::vector<Regra*>& Processador::getRegras() const {
    return regras;
}

void Processador::removerAssociacaoAparelho() {
    aparelho= nullptr;
}


bool Processador::avaliaRegras() {
    if(aparelho== nullptr){ ;
        return false;

    }
    bool todasRegrasCorretas=true;
    for(Regra *regra:regras){
        if(!regra->verificar()){
            todasRegrasCorretas = false;
            break;
        }
    }
    if (todasRegrasCorretas) {
        comandoProc=getComando();


        // Verificar o valor do comando
        if (comandoProc == "liga") {

                aparelho->ligar();



        } else if (comandoProc== "desliga") {

                aparelho->desligar();



        } else {
            cout << "Comando desconhecido: " << comandoProc << "\n";
        }
        return true;
    } else {
        cout << "Nem todas as regras sao verdadeiras.\n";
        return false;
    }

}


string Processador::getnome() {
    return nome;
}

void Processador::setNome(const string &novoNome) {
    nome = novoNome;
}