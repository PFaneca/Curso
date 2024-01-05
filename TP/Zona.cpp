//
// Created by ASUS on 01/11/2023.
//

#include "utils.h"
#include "Zona.h"
#include "Propriedades/Temperatura.h"
#include "Propriedades//Fumo.h"
#include "Propriedades//Humidade.h"
#include "Propriedades//Luz.h"
#include "Propriedades//Radiacao.h"
#include "Propriedades//Som.h"
#include "Propriedades//Vibracao.h"
#include "Regras/Maior.h"
#include "Regras/Entre.h"
#include "Regras/Fora.h"
#include "Regras/Igual.h"
#include "Regras/Menor.h"

using namespace std;
using namespace term;

//Zona::Zona(int x,int y): x(x),y(y) ,ocupada(false) {id_z=++contador_z;}
Zona::Zona()  {

    criarProp();
    id_z=++contador_z;}

    int Zona::contador_z=0;

Zona::~Zona() {
    for (Sensor* sensor : sensores) {
        delete sensor;
    }

    for(Aparelho *aparelho : aparelhos){
        delete aparelho;
    }
   for(Processador *processador : processadores){
       delete processador;
   }


}
int Zona::getId() const {
    return id_z;
}



string Zona::getString() const{
    ostringstream os;
    os << "Zona " << id_z << "na linha = " << linha << "e coluna= " << coluna;
    return os.str();
}



void Zona::AdicionarPropriedade(const Propriedade &propriedade) {
    propriedades.push_back(propriedade);
}
void Zona::criarProp() {
    this->AdicionarPropriedade(Temperatura());
    this->AdicionarPropriedade(Fumo());
    this->AdicionarPropriedade(Humidade());
    this->AdicionarPropriedade(Luz());
    this->AdicionarPropriedade(Radicao());
    this->AdicionarPropriedade(Som());
    this->AdicionarPropriedade(Vibracao());
}

void Zona::listarPropriedades(Window &infos) const {
    infos  << set_color(0)<< "Propriedades na zona " << id_z << ":\n";
    for ( auto &propriedade: propriedades) {
        infos << set_color(0)<< "(" << propriedade.gettipo() << "," << propriedade.getvalor() << propriedade.getunidade() << " ) \n";
    }
}

void Zona::modificarProp(const std::string& nome, double novoValor, Window &infos) {
    for (auto& propriedade : propriedades) {
        if (propriedade.gettipo() == nome) {
            propriedade.setvalor(novoValor);
            infos << set_color(0)<< "Valor da Propriedade alterado\n";
            return;
        }
    }

    // Se o loop terminar e não encontrarmos a propriedade
    infos << set_color(0)<< "Propriedade com o nome " << nome << " não encontrada.\n";
}




void Zona::AdicionarSensor(Propriedade* prop,Window &infos) {
    sensores.emplace_back(new Sensor(prop));
    infos << set_color(0)<< "Sensor adicionado. ID: " << sensores.back()->letra() << sensores.back()->getId() << "\n";

}
int Zona::getultimosensor() const {
    if (!sensores.empty()) {
        return sensores.back()->getId();
    }
}

string Zona::getletraultimosensor() const {
    if(!sensores.empty()){
        return sensores.back()->letra();
    }
}

void Zona::RemoverSensor(int idsensor,Window &infos) {
    for(auto it=sensores.begin();it!=sensores.end();++it){
        if((*it)->getId()==idsensor){
            if (Sensorassociadoregra(idsensor)) {
                infos << set_color(4) << "Não é possível remover o sensor " << idsensor << " pois está associado a regras.\n";
                return;
            }

            delete *it;
             sensores.erase(it);
             infos << "Sensor " << idsensor << " removido\n";
            return;
        }
    }
   infos << set_color(4)<< "Sensor com id: " << idsensor << " nao encontrado na zona\n";
}

bool Zona::Sensorassociadoregra(int id_sensor) const {
    for(const auto &regra : regras){
        if(regra->contemSensor(id_sensor)){
            return true;
        }
    }
    return false;
}

void Zona::listarSensores(Window &infos)const {
    for(auto p:sensores){
        infos << set_color(0) << p->letra() << p->getId() << " : " <<p->gettipo() <<" ( " << p->getvalor_prop() << p->getunidade() << " )\n ";
    }

}

Sensor *Zona::encontrarSensor(int idSensor) const{
    for(Sensor *sensor:sensores){
        if(sensor->getId()==idSensor){
            return sensor;
        }
    }
    return nullptr;
}



void Zona::AdicionarAparelhos(Aparelho* aparelho,Window &infos) {
    aparelhos.push_back(aparelho);

    for ( auto it = propriedades.begin(); it != propriedades.end(); it++) {
        aparelho->AdicionarPropriedade(*it);
    }

}

void Zona::RemoverAparelho(int idaparelho, Window &infos) {
    for (auto it = aparelhos.begin(); it != aparelhos.end(); ++it) {
        if ((*it)->getId() == idaparelho) {
            for (const Processador* proc : processadores) {
                 if (proc->getAparelhoAssociado() && proc->getAparelhoAssociado()->getId() == idaparelho) {
                if(proc->getAparelhoAssociado() && proc->getAparelhoAssociado()->getId() )
                     infos << set_color(4)<< "Nao e possivel remover o aparelho, pois esta associado a um processador.\n";
                    return;
                }

            }
            delete *it;
            aparelhos.erase(it);
            infos << "Aparelho " << idaparelho << " removido\n";
            return;
        }
    }
    infos << "Aparelho com ID " << idaparelho << " não encontrado na zona.\n";
}
void Zona::listarAparelhos(Window &infos)const {
    for(auto p: aparelhos){
            infos << set_color(0)<< p->getletra() << p->getId() << " : " << p->getnome() << "(comando:" << p->getComando()<< ")\n";

    }

}

Aparelho *Zona::encontraAparelho(int idAparelho) {
    for(auto aparelho:aparelhos){
        if(aparelho->getId()==idAparelho){
            return aparelho;
        }
    }
    return nullptr;
}


void Zona::AdicionarProcessador(Processador *proc) {
    processadores.emplace_back(proc);
}

void Zona::RemoverProc(int idproc,Window &infos) {
    for(auto it=processadores.begin();it!=processadores.end();++it){
        if((*it)->getAparelhoAssociado()){
                infos << set_color(4) <<  "Nao e possivel remover o processador p" << idproc << " pois esta associado a um aparelho\n";
               return;
             }


            else if(!(*it)->getRegras().empty()){
                infos << set_color(4) << "Nao e possivel remover o processador p" << idproc << " pois tem regras associadas\n";
                return;
            }

            delete *it;
            it=processadores.erase(it);
            infos << set_color(0) << "Processador "<< idproc<< " removido" <<"\n";
            return;
        }

    infos << "Processaor com ID " << idproc << " não encontrado na zona.\n";
}

void Zona::ListarProcessadores(Window &infos) {
    for (auto p: processadores) {
        infos  << set_color(0)<< p->getletra() << p->getId()  << " (Processador) com " << p->contaRegras() << " regras associadas\n";
    }
}

bool Zona::mudarComandoProc(int idProc,string novoComando,Window &infos) {
    for(auto &proc:processadores){
        if(proc->getId()==idProc){
            proc->setComando(novoComando);
            return true;
        }
    }
    infos << "Processador com ID " << idProc << " não encontrado na zona.\n";
    return false;
}

Processador* Zona::encontrarProcessador(int idProc) {
    for(auto proc : processadores){
        if(proc->getId() == idProc){
            return proc;
        }
    }
    return nullptr;
}


void Zona::AssociarAparelho_Proc(int idProcessador, int idAparelho,Window &infos) {
    for(Processador *proc : processadores){
        if(proc->getId()==idProcessador){
            Aparelho *aparelho= encontraAparelho(idAparelho);
            if(aparelho){
                proc->associarAparelho(aparelho);
                infos << set_color(0)<< "Associado o processador p" << idProcessador << " com o aparelho a" << idAparelho<<"\n";
            }
            else{
                infos << set_color(4)<< "Aparelho não encontrado na zona.\n";
            }
            return;
        }
    }
    infos << set_color(4)<<"Processador de regras com ID p" << idProcessador << " não encontrado na zona.\n";
}

void Zona::DesassociarAparelho_Proc(int idProcessador, int idAparelho,Window &infos) {
    for(Processador *proc:processadores){
        if(proc->getId()==idProcessador){
            Aparelho *aparelho= encontraAparelho(idAparelho);
            if(aparelho){
                proc->removerAssociacaoAparelho();
                infos << set_color(0)<< "Desassociacao realizada com sucesso \n" ;
                return;
            }

        }
    }
    infos << set_color(4)<< "Processador de regras com ID: p" << idProcessador << " não encontrado na zona.\n";
}


void Zona::enviarcomandoAparelho(int id_aparelho,string comando,Window &infos) {
    for(Aparelho *aparelho : aparelhos){
        if(aparelho->getId()==id_aparelho){
            aparelho->AtualizarComando(comando,infos);
            infos << set_color(0)<< "Enviado o comando " << comando << " para o aparelho a" << id_aparelho << "\n";
            return;
        }
    }
    infos << set_color(4)<< "Aparelho ID: a" << id_aparelho << " não encontrado na zona.\n";
}





void Zona::criarRegra(int idProc,const std::string &nomeRegra,int idSensor,double arg1,double arg2,Window &infos) {
    Sensor *sensor= encontrarSensor(idSensor);
    Processador *proc= encontrarProcessador(idProc);
    if(proc && sensor){
        Regra *novaregra = nullptr;
        if(nomeRegra == "entre"){
            novaregra = new Regra_entre(*sensor,arg1,arg2);

        }
        else if(nomeRegra == "fora"){
            novaregra = new Regra_Fora(*sensor,arg1,arg2);
        }
        else{
            infos << set_color(4) << "Regra " << nomeRegra << " nao existe";
        }

        proc->AdicionarRegra(novaregra);
        infos << set_color(0)<< "Regra " << novaregra->gettipo() << novaregra->getId() << " associado ao sensor s" << idSensor << " e processador p" << idProc << "\n";


        if(proc->avaliaRegras()){
            Aparelho * aparelhoAssociado = proc->getAparelhoAssociado();
            if(aparelhoAssociado){
                aparelhoAssociado->AtualizarComando(proc->getComando(), infos);
            }

        }

    }else{
        infos << set_color(4)<<  "Sensor ou Processador" << " não encontrado na zona.\n" ;
    }
}

void Zona::criarRegra(int idProc, const std::string &nomeRegra, int idSensor, double arg1,Window &infos) {
    Sensor *sensor = encontrarSensor(idSensor);
    Processador *proc = encontrarProcessador(idProc);
    if (proc && sensor) {
        Regra *novaregra = nullptr;
        if (nomeRegra == "maior_que") {
            novaregra = new Regra_Maior(*sensor, arg1);
        }
        else if(nomeRegra=="igual_a"){
             novaregra = new Regra_Igual(*sensor,arg1);
        }
        else if(nomeRegra=="menor_que"){
            novaregra = new Regra_Menor(*sensor,arg1);
        }

        proc->AdicionarRegra(novaregra);
        infos <<set_color(0)<< "Regra "  << novaregra->gettipo() << novaregra->getId() << " associado ao sensor s" << idSensor << " e processador p" << idProc <<"\n";
        //if(proc->avaliaRegras()){
        //    Aparelho * aparelhoAssociado = proc->getAparelhoAssociado();
        //    if(aparelhoAssociado){
        //        aparelhoAssociado->AtualizarComando(proc->getComando(),infos);
          //  }
        //}
    } else {
        infos << set_color(4)<< "Sensor ou Processador" << " não encontrado na zona.\n";
    }
}
void Zona::listarRegras(int idProc,Window &infos) {
    Processador *proc= encontrarProcessador(idProc);
    if(proc){
        proc->ListarRegras(infos);
    }

}

void Zona::removerRegra(int idproc, int idregra,Window &infos) {
    Processador *proc= encontrarProcessador(idproc);
    if(proc){
        if(proc->RemoverRegra(idregra)){
            infos << set_color(0)<< "Regra com ID " << idregra << " removida do processador " << idproc << "\n";
        }
        else{
            infos << set_color(4)<< "Regra com ID " << idregra << " não encontrada no processador " << idproc << "\n";
        }
    }
    else {
        infos << set_color(4)<< "Processador não encontrado na zona.\n";
    }
}



void Zona::avaliaRegras(Window &infos) {
    for(auto proc:processadores){
        if(proc->avaliaRegras()){
            Aparelho * aparelhoAssociado = proc->getAparelhoAssociado();
            if(aparelhoAssociado){
                aparelhoAssociado->AtualizarComando(proc->getComando(),infos);
            }
        }
    }
}


int Zona::getNumeroSensores() const {
    return sensores.size();
}

int Zona::getNumeroAparalhos() const {
    return aparelhos.size();
}

int Zona::getNumeroProcessadores() const {
    return processadores.size();
}


void Zona::SalvaProc(int id_proc, string &nome,Window &infos) {
    Processador *proc= encontrarProcessador(id_proc);
    if(!proc){
        infos << set_color(4) << "Processador p" << id_proc << " nao encontrado";
        return;
    }
    Processador *copia_processador=new Processador(*proc);

    copia_processador->setNome(nome);
    processadoresSalvos.push_back(copia_processador);
    infos << set_color(0) << "Estado do processador salvo com sucesso. Nome: " << nome << "\n";
}

void Zona::Listacopiasproc(Window &infos) {

    infos << "Lista de copias de processadores salvos: \n";
    for( auto proc:processadoresSalvos){
        infos << set_color(0) << "Nome: " <<proc->getnome() << ",ID Processador p" << proc->getId() << ",ID Zona: " << getId() << "\n";
    }
}


void Zona::ReporProcSalvo(string &nome, term::Window &infos) {
    Processador* processadorSalvo = nullptr;
    for (Processador* savedProc : processadoresSalvos) {
        if (savedProc->getnome() == nome) {
            processadorSalvo = savedProc;
            break;
        }
    }
    if (!processadorSalvo) {
        infos << set_color(4) << "Processador com o nome '" << nome << "' não encontrado.\n";
        return;
    }
    Zona *zonaoriginal= nullptr;

}

void Zona::ApagarProcSalvo(string nome,Window &infos) {

    for(auto it=processadoresSalvos.begin();it!=processadoresSalvos.end();++it){
        if((*it)->getnome()==nome){
            infos << set_color(10) <<"Copia do processador " << nome << " apagada com sucesso.\n";
            delete *it;
            it=processadoresSalvos.erase(it);

            return;
        }
        else {
            infos << set_color(4) <<"Cópia do processador " << nome << " não encontrada.\n";
        }
    }
}




/*
void Zona::ExibirPropAlteradas(Window &infos) {
    for (auto &prop : propriedades) {
        const std::string &nomePropriedade = prop.gettipo();
        double valorAntes = prop.getvalor();
        double valorDepois = prop.getvalor();

        if (valorAntes != valorDepois) {
            infos << set_color(0) << "Propriedade " << nomePropriedade << " na zona " << getId() << ": ";
            infos << "Valor Antes: " << valorAntes << ", Valor Depois: " << valorDepois << "\n";
        }
    }
}

*/





