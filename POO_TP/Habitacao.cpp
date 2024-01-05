//
// Created by ASUS on 05/12/2023.
//

#include "Habitacao.h"
#include <vector>

using namespace term;
using namespace std;
Habitacao::Habitacao() {

}
void Habitacao::criarhabitacao(int linhas, int colunas) {
    this->numlinhas = linhas;
    this->numcolunas = colunas;


    for(int j = 1; j <= colunas * linhas; j++)
        mapWin.clear();

    int larguraTotal = 80;
    int alturaTotal = 24;
    int larguraZona = larguraTotal / colunas ;
    int alturaZona = alturaTotal / linhas;
    int x = 1;
    int y = 1;
    int count = 0;

    for (int i = 1; i <= linhas * colunas; i++) {

        mapWin.emplace(i, term::Window(x, y, larguraZona, alturaZona));

        x += (larguraTotal / colunas);
        count++;

        if (count >= colunas) {
            y += alturaTotal / linhas;
            x = 1;
            count = 0;
        }

    }
}





Habitacao::~Habitacao() {

}

void Habitacao::removerHabitacao() {

    mapWin.clear();
    numlinhas = 0;
    numcolunas = 0;
}


void Habitacao::criarzona(int linha, int coluna,Window &infos) {
    int posicao = (linha - 1) * numcolunas + coluna;

    if (linha > 0 && linha < numlinhas+1  && coluna > 0 && coluna < numcolunas +1) {
        // Verifica se a posição está vazia
        if (zonas.find(posicao) == zonas.end()) {
            // Cria uma nova zona
            Zona novaZona;
            int id_zona = novaZona.getId();

            // Adiciona a zona ao mapa
            zonas[posicao] = novaZona;

            // Adiciona a janela ao mapa de janelas (suponho que term::Window seja o tipo correto)

            auto it = mapWin.find(posicao);
            it->second << "Zona " << it->first << "\n";
            //it->second << "s: " << "\t";
            //it->second << "a: " << "\t";
            //it->second << "p: " << "\t";

        } else {
            infos << "A posicao (" << linha << ", " << coluna << ") ja esta ocupada por uma zona\n";
        }
    }
}


void Habitacao::removerzona(int id_zona,Window &info) {

    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){


        zonas.erase(itzona);
        auto itwin = mapWin.find(id_zona);
        if(itwin!=mapWin.end()){
            itwin->second.clear();

        }

        info << set_color(0)<<"Zona com ID " << id_zona << " removida com sucesso.\n";
    }
    else{
        info << set_color(4)<<"Zona com ID " << id_zona << " nao encontrada.\n";
    }

}
void Habitacao::listarZonas(Window &infos) {
    infos << set_color(0) <<"Zonas na habitacao:\n";

    for (const auto& p : zonas) {
        const Zona& zona = p.second;
        int id_zona = p.first;

        infos << "Zona " << id_zona<< "\n";
        int numsensores = zona.getNumeroSensores();
        int numaparelhos = zona.getNumeroAparalhos();
        int numprocessadores = zona.getNumeroProcessadores();
        infos << set_color(0) << "Sensores: " << numsensores << "\n";
        infos << set_color(0) << "Aparelhos: " << numaparelhos << "\n";
        infos << set_color(0) <<"Processadores: " << numprocessadores << "\n";
    }

}




void Habitacao::listarPropriedades(int id_zona,Window &infos) {

    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
           itzona->second.listarPropriedades(infos);
    }
    else
        infos << set_color(0)<< "Zona nao encontrada.\n";

}


void Habitacao::modificarprop(int id_zona, const string &nome, double novovalor,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
        itzona->second.modificarProp(nome,novovalor,infos);
    }
    else
        infos << set_color(0)<< "Zona não encontrada.\n";
}


void Habitacao::adicionaSensor(int id_zona, Propriedade *prop,Window &infos) {
    auto itzona = zonas.find(id_zona);

    if (itzona != zonas.end()) {
        itzona->second.AdicionarSensor(prop, infos);
    } else {
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }

    // Note que o código abaixo está fora do bloco else,
    // portanto, será executado independentemente se a zona foi encontrada ou não
    int ultimosensor = itzona->second.getultimosensor();
    string letra = itzona->second.getletraultimosensor();
    string letra_visualizacao;
    if(prop->gettipo()=="Temperatura"){
       letra_visualizacao = "t";
    }
    else if(prop->gettipo()== "Fumo"){
        letra_visualizacao = "f";
    }
    else if(prop->gettipo()=="Humidade"){
        letra_visualizacao = "h";
    }
    else if(prop->gettipo() == "Luz"){
        letra_visualizacao = "m";
    }
    else if(prop->gettipo()=="Radiacao"){
        letra_visualizacao = "d";
    }
    else if(prop->gettipo()=="Som"){
        letra_visualizacao = "o";
    }
    else if(prop->gettipo()=="Vibracao"){
        letra_visualizacao = "v";
    }

    auto itwin = mapWin.find(id_zona);
    itwin->second << letra << ultimosensor << " "<< letra_visualizacao << "\t";


}



void Habitacao::removerSensor(int id_zona, int idsensor,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
        itzona->second.RemoverSensor(idsensor,infos);
    }
    else
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";

}

void Habitacao::ListarSensores(int id_zona,Window &infos) const {
    auto it_zona=zonas.find(id_zona);
    if(it_zona!=zonas.end()){
        it_zona->second.listarSensores(infos);
    }
    else
    infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";


}


void Habitacao::AdicionaProc(int id_zona, Processador *proc,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
       itzona->second.AdicionarProcessador(proc);
        infos << set_color(0) << "Processador adicionado. ID: " << proc->getletra()<< proc->getId() << "\n";
    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }


    auto itwin=mapWin.find(id_zona);
    itwin->second<<proc->getletra() << proc->getId() << "\t";
}

void Habitacao::RemoverProc(int id_zona, int idproc,Window &infos) {
    auto it_zona=zonas.find(id_zona);
    if(it_zona!=zonas.end()){
        it_zona->second.RemoverProc(idproc,infos);
    }
    else
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
}

void Habitacao::ListarProcessadores(int id_zona,Window &infos) {
    auto it_zona=zonas.find(id_zona);
    if(it_zona!=zonas.end()){
        it_zona->second.ListarProcessadores(infos);
    }
    else
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
}

void Habitacao::mudarComandoProc(int id_zona, int id_proc, string novoComando,Window &infos) {
    auto it_zona=zonas.find(id_zona);
    if(it_zona!=zonas.end()){
        it_zona->second.mudarComandoProc(id_proc,novoComando,infos);
    }
    else
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
}


void Habitacao::AdicionaAparelho(int id_zona, Aparelho *aparelho,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
       itzona->second.AdicionarAparelhos(aparelho,infos);
        infos << set_color(0) << "Aparelho adicionado. ID: " << aparelho->getletra()<< aparelho->getId() <<  "\n";
    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }


    auto itwin=mapWin.find(id_zona);
    itwin->second<<aparelho->getletra() << aparelho->getId() <<  " " << aparelho->gettipo() <<"\t";

}

void Habitacao::RemoverAparelho(int id_zona, int idaparelho,Window &infos) {
    auto it_zona=zonas.find(id_zona);
    if(it_zona!=zonas.end()){
        it_zona->second.RemoverAparelho(idaparelho,infos);
    }
    else
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
}


void Habitacao::ListarAparelhos(int id_zona,Window &infos) {
    auto it_zona=zonas.find(id_zona);
    if(it_zona!=zonas.end()){
        it_zona->second.listarAparelhos(infos);
    }
    else
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
}


void Habitacao::criarRegra(int id_zona, int id_proc, const string &nomeRegra, int id_sensor,double arg1,double arg2,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
        itzona->second.criarRegra(id_proc,nomeRegra,id_sensor,arg1,arg2,infos);

    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }
}

void Habitacao::criarRegra(int id_zona, int id_proc, const string &nomeRegra, int id_sensor, double arg1,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
       itzona->second.criarRegra(id_proc,nomeRegra,id_sensor,arg1,infos);

    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }
}

void Habitacao::ListarRegras(int id_zona, int id_proc,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
        itzona->second.listarRegras(id_proc,infos);

    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }
}


void Habitacao::removerRegra(int id_zona, int id_proc, int id_regra,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
        itzona->second.removerRegra(id_proc,id_regra,infos);

    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }
}



void Habitacao::AssociarProcAparelho(int id_zona, int id_proc, int id_aparelho,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
        itzona->second.AssociarAparelho_Proc(id_proc,id_aparelho,infos);

    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }
}


void Habitacao::DesassociarProcAparelho(int id_zona, int id_proc, int id_aparelho,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
        itzona->second.DesassociarAparelho_Proc(id_proc,id_aparelho,infos);

    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }
}

void Habitacao::EnviarcomandoAparelho(int id_zona, int id_aparelho, string comando,Window &infos) {
    auto itzona=zonas.find(id_zona);
    if(itzona!=zonas.end()){
        itzona->second.enviarcomandoAparelho(id_aparelho,comando,infos);

    }
    else{
        // Se chegou aqui, não encontrou a zona com o ID especificado
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }
}


void Habitacao::SalvaProc(int id_zona, int id_proc, string &nome,Window &infos) {
    auto it_zona=zonas.find(id_zona);
    if(it_zona!=zonas.end()){
        it_zona->second.SalvaProc(id_proc,nome,infos);
    }
    else{
        infos << set_color(4)<< "Zona com ID " << id_zona << " nao encontrada.\n";
        return;
    }
}


void Habitacao::ListacopiasProc(Window &infos) {
    for( auto &zona:zonas){
        infos << set_color(0) << "Zona " << zona.first << "\n";
        zona.second.Listacopiasproc(infos);
        infos << "\n";
    }
}

void Habitacao::ApagarProcSalvo(string &nome,Window &infos) {
    for(auto zona:zonas){
        zona.second.ApagarProcSalvo(nome,infos);
    }
}



int Habitacao::getInstantes() {
    return instantes;
}

void Habitacao::Prox(Window &infos) {
    instantes+=1;


    for (auto &par: zonas) {
        Zona &zona = par.second;
        zona.avaliaRegras(infos);
       // zona.AtualizarValoresProp();
    }
}

void Habitacao::Avanca(int n) {
    instantes+=n;
}