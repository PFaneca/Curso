//
// Created by ASUS on 13/12/2023.
//

#include "Interacao.h"
#include "Terminal.h"
using namespace std;

using namespace term;


Interacao::Interacao() : cmd(0,25,82,5,true),infos(83,0,35,30,true){}


int Interacao::leComando(){
    string comando,linhas;
    do{
        cmd << set_color(11)<<"Instante: " << habitacao.getInstantes() << "\n";
        cmd << set_color(0) << "Escreva o comando: ";
        cmd >> comando;
        checkcomando(comando);
        if(comando=="sair"){
            return 0;
        }
    }while(linhas!="sair");
}


void Interacao::checkcomando(string frase) {
    string comando, lixo;
    istringstream iss(frase);
    iss >> comando;
    vector<std::string> args;
    std::vector<std::string> argumentos;

    // Lê todos os argumentos disponíveis
    while (!iss.eof()) {
        std::string arg;
        iss >> arg;
        argumentos.push_back(arg);
    }

    if (comando == "prox") {

        if (argumentos.size()==0){
            infos << set_color(10) << "Comando valido!\n";
            habitacao.Prox(infos);
        }

        else
            infos << set_color(4) << "Comando invalido\n";

    } else if (comando == "avanca") {

        if (argumentos.size() == 1) {
            try {
                int n = stoi(argumentos[0]);
                infos << set_color(10) << "Comando valido!\n";
                infos << set_color(0) << "Avanca " << n << " instantes\n";
                habitacao.Avanca(n);
            } catch (invalid_argument &) {
                infos << set_color(4) << "Comando invalido! O argumento deve ser um numero.\n";
            }
        } else {
            infos << set_color(4) << "Comando invalido! Forneca exatamente um argumento.\n";
        }

    } else if (comando == "hnova") {
        if (argumentos.size() == 2) {
            try {
                int linhas = stoi(argumentos[0]);
                int colunas = stoi(argumentos[1]);
                if ((linhas >= 2 && linhas <= 4) && (colunas >= 2 && colunas <= 4)) {
                    infos << set_color(10) << "Comando valido\n";
                    infos << set_color(0) << "Criar habitacao " << linhas << "x" <<colunas << "\n";
                    habitacao.criarhabitacao(linhas, colunas);
                }
                else{
                    infos << set_color(4) << "Limite entre 2x2 a 4x4\n";
                }
            } catch (invalid_argument &) {
                infos << set_color(4)<< "Comando invalido! O numero de linhas e colunas tem de ser numeros inteiros\n";
            }
        } else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="hrem"){
        if(argumentos.size()==0){
            infos << set_color(10) << "Comando valido\n";
            habitacao.removerHabitacao();
        }
        else
            infos << set_color(4) << "Comando invalido\n";

    }

    else if(comando=="znova"){
        if(argumentos.size()==2){
            try{
                int linha=stoi(argumentos[0]);
                int coluna = stoi(argumentos[1]);
                infos << set_color(10) << "Comando valido\n";
                infos << set_color(0) << "Criar zona na linha " << linha << " e coluna " << coluna << '\n';
                habitacao.criarzona(linha,coluna,infos);
            }catch (invalid_argument&){
                infos << set_color(4)<<"Comando invalido! O numero da linha e coluna tem de ser numeros inteiros\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="zrem"){
        if(argumentos.size()==1){
            try{
                int id_zona=stoi(argumentos[0]);
                infos << set_color(10) << "Comando valido\n";
                infos << set_color(0) <<"Apagar zona com id "<< id_zona << '\n';
                habitacao.removerzona(id_zona,infos);


            }catch (invalid_argument&){
                infos << set_color(4)<< "Comando invalido! O id da zona tem de ser um numero inteiro\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="zlista"){
        if(argumentos.size()==0){
            infos << set_color(10) << "Comando valido\n";
            habitacao.listarZonas(infos);
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="zcomp"){
        if(argumentos.size()==1){
            try{
                int id_zona= stoi(argumentos[0]);
                infos << set_color(10) << "Comando valido\n";
                habitacao.ListarSensores(id_zona,infos);
                habitacao.ListarProcessadores(id_zona,infos);
                habitacao.ListarAparelhos(id_zona,infos);

            }catch (invalid_argument&){
                infos << set_color(4)<< "Comando invalido! O id da zona tem de ser um numero inteiro\n";

            }
        }
        else{
            infos << set_color(4) << "Comando invalido\n";
        }
    }

    else if(comando=="zprops"){
            if(argumentos.size()==1){
                try{
                    int id_zona= stoi(argumentos[0]);
                    infos << set_color(10) << "Comando valido\n";
                    habitacao.listarPropriedades(id_zona,infos);

                }catch (invalid_argument&){
                    infos << set_color(4)<< "Comando invalido! O id da zona tem de ser um numero inteiro\n";

                }
            }
            else
                infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="pmod"){
        if(argumentos.size()==3){
            try{
                int id_zona=stoi(argumentos[0]);
                string nome_prop=argumentos[1];
                double valor_novo=stod(argumentos[2]);
                infos << set_color(10) << "Comando valido\n";
                habitacao.modificarprop(id_zona,nome_prop,valor_novo,infos);

            }catch (invalid_argument&){
                infos << set_color(4)<< "Comando invalido! Digite pmov <id_zona> <nome_prop> <valor_novo>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if (comando == "cnovo") {
        if (argumentos.size() == 3) {
            try {
                int id_zona = stoi(argumentos[0]);
                string componente = argumentos[1];
                string tipo = argumentos[2];

                if (componente.size() == 1 && isalpha(componente[0])) {
                    if (componente == "s") {
                        if (tipo == "temperatura") {
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar sensor de " << tipo << '\n';
                            habitacao.adicionaSensor(id_zona, new Temperatura, infos);
                        }
                        else if(tipo=="fumo"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar sensor de " << tipo << '\n';
                            habitacao.adicionaSensor(id_zona, new Fumo, infos);
                        }
                        else if(tipo=="humidade"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar sensor de " << tipo << '\n';
                            habitacao.adicionaSensor(id_zona, new Humidade, infos);
                        }
                        else if(tipo=="luz"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar sensor de " << tipo << '\n';
                            habitacao.adicionaSensor(id_zona, new Luz, infos);
                        }
                        else if(tipo=="radiacao"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar sensor de " << tipo << '\n';
                            habitacao.adicionaSensor(id_zona, new Radicao, infos);
                        }
                        else if(tipo=="som"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar sensor de " << tipo << '\n';
                            habitacao.adicionaSensor(id_zona, new Som, infos);
                        }
                        else if(tipo=="vibracao"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar sensor de " << tipo << '\n';
                            habitacao.adicionaSensor(id_zona, new Vibracao, infos);
                        }
                        else{
                            infos << set_color(4)<<"Propriedade desconhecida\n";


                        }

                    }
                    else if(componente=="p"){
                        if(tipo=="liga") {
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar procesador de regras com comando " << tipo << '\n';
                            habitacao.AdicionaProc(id_zona, new Processador("liga"), infos);
                        }
                        else if(tipo=="desliga"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar procesador de regras com comando " << tipo << '\n';
                            habitacao.AdicionaProc(id_zona, new Processador("desliga"), infos);
                        }
                        else{
                            infos << set_color(4)<< "Comando desconhecido\n";
                        }
                    }

                    else if(componente=="a"){
                        if(tipo=="aquecedor"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar aparelho: " << tipo << '\n';
                            habitacao.AdicionaAparelho(id_zona,new Aquecedor(),infos);
                        }
                        else if(tipo=="aspersor"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar aparelho: " << tipo << '\n';
                            habitacao.AdicionaAparelho(id_zona,new Aspersor,infos);
                        }
                        else if(tipo=="refrigerador"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar aparelho: " << tipo << '\n';
                            habitacao.AdicionaAparelho(id_zona,new Refrigerador,infos);
                        }
                        else if(tipo=="lampada"){
                            infos << set_color(10) << "Comando valido\n";
                            infos << set_color(0) << "Na zona " << id_zona << " adicionar aparelho: " << tipo << '\n';
                            habitacao.AdicionaAparelho(id_zona,new Lampada,infos);
                        }
                        else{
                            infos << set_color(4)<<"Aparelho desconhecido\n";
                        }
                    }
                    else{
                        infos << set_color(4)<<"Tipo de componete desconhecido\n";
                    }
                    // Adicione outras condições conforme necessário
                }
                else{
                    infos << set_color(4) << "So pode adicionar s(sensor), p(processador),a(aparelho)\n";
                }
            } catch (invalid_argument&) {
                infos  << set_color(4)<< "Comando invalido! Digite cnovo <id_zona> <s|p|a> <tipo|comando>\n";
            }
        } else {
            infos << set_color(4) << "Comando invalido\n";
        }
    }

    else if(comando=="crem") {
        if (argumentos.size() == 3) {
            try {
                int id_zona = stoi(argumentos[0]);
                string componente = argumentos[1];
                char tipo_componente = argumentos[2][0];
                int valor_inteiro = stoi(argumentos[2].substr(1));
                if (componente.size() == 1 && isalpha(componente[0])) {
                    if (componente == "s") {
                        infos << set_color(10) << "Comando valido\n";
                        infos << set_color(0) << "Na zona" << id_zona << " remover sensor " << tipo_componente<< valor_inteiro << "\n";
                        habitacao.removerSensor(id_zona, valor_inteiro, infos);
                    } else if (componente == "p") {
                        infos << set_color(10) << "Comando valido\n";
                        infos << set_color(0) << "Na zona" << id_zona << " remover processadpr " << tipo_componente<< valor_inteiro << "\n";
                        habitacao.RemoverProc(id_zona, valor_inteiro, infos);
                    }
                    else if(componente=="a"){
                        infos << set_color(10) << "Comando valido\n";
                        infos << set_color(0) << "Na zona" << id_zona << " remover aparelho " << tipo_componente<< valor_inteiro << "\n";
                        habitacao.RemoverAparelho(id_zona,valor_inteiro,infos);
                    }

                }
                else{
                    infos << set_color(4) << "So pode remover s(sensor), p(processador),a(aparelho)\n";
                }
            } catch (invalid_argument &) {
                infos << set_color(4) << "Comando invalido!Digite crem <id_zona> <s|p|a> <id_componente>\n";
            }
        } else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="rnova") {
        try {

            if (argumentos.size() == 6) {
                int id_zona = stoi(argumentos[0]);
                char letra_proc = argumentos[1][0];
                int valor_inteiro_proc = stoi(argumentos[1].substr(1));
                string regra = argumentos[2];
                char letra_sensor = argumentos[3][0];
                int valor_inteiro_sensor = stoi(argumentos[3].substr(1));
                int x = stod(argumentos[4]);
                int y = stod(argumentos[5]);
                infos << set_color(10) << "Comando valido\n";
                habitacao.criarRegra(id_zona, valor_inteiro_proc, regra, valor_inteiro_sensor, x, y, infos);

            } else if (argumentos.size() == 5) {
                int id_zona = stoi(argumentos[0]);
                char letra_proc = argumentos[1][0];
                int valor_inteiro_proc = stoi(argumentos[1].substr(1));
                string regra = argumentos[2];
                char letra_sensor = argumentos[3][0];
                int valor_inteiro_sensor = stoi(argumentos[3].substr(1));
                double x = stod(argumentos[4]);
                infos << set_color(10) << "Comando valido\n";
                habitacao.criarRegra(id_zona, valor_inteiro_proc, regra, valor_inteiro_sensor, x, infos);
            }
            else{
                infos << set_color(4) << "Comando invalido\n";
            }
        }catch (invalid_argument &){
            infos << set_color(4)<< "Comando invalido!Digite rnova <id_zona> <id_processador> <regra> <id_sensor> [param1] [param2] [...]\n";
        }
    }

    else if(comando=="pmuda"){
        if(argumentos.size()==3){
            try{
                int id_zona=stoi(argumentos[0]);
                char letra_proc=argumentos[1][0];
                int valor_inteiro_proc = stoi(argumentos[1].substr(1));
                string novo_comando = argumentos[2];
                infos << set_color(10) << "Comando valido\n";
                infos << set_color(0)<< "Na zona " << id_zona << " ,no processador " << letra_proc << valor_inteiro_proc << " ,o novo comando e " << novo_comando << '\n';
                habitacao.mudarComandoProc(id_zona,valor_inteiro_proc,novo_comando,infos);
            }catch (invalid_argument &){
                infos << "Comando invalido!Digite pmuda <id_zona> <id_proc.regras> <novo comando>\n";
            }
        }
        else{
            infos << set_color(4) << "Comando invalido\n";
        }
    }

    else if(comando=="rlista"){
        if(argumentos.size()==2){
            try{
                int id_zona=stoi(argumentos[0]);
                char letra_proc=argumentos[1][0];
                int valor_inteiro_proc = stoi(argumentos[1].substr(1));
                infos << set_color(10) << "Comando valido\n";
                habitacao.ListarRegras(id_zona,valor_inteiro_proc,infos);
            }catch (invalid_argument &){
                infos << set_color(4) << "Comando invalido!Digite rlista <id_zona> <id_proc.regras>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="rrem"){
        if(argumentos.size()==3){
            try{
                int id_zona=stoi(argumentos[0]);
                char letra_proc=argumentos[1][0];
                int valor_inteiro_proc = stoi(argumentos[1].substr(1));
                char letra_regra = argumentos[2][0];
                int valor_inteiro_regra=stoi(argumentos[2].substr(1));
                infos << set_color(10) << "Comando valido\n";
                infos << set_color(0)<<"Na zona " << id_zona << " no processador de regras " << letra_proc << valor_inteiro_proc << " remover a regra " << letra_regra<< valor_inteiro_regra << '\n';
                habitacao.removerRegra(id_zona,valor_inteiro_proc,valor_inteiro_regra,infos);
            }catch (invalid_argument &){
                infos << set_color(4) <<"Comando invalido! Digite rrem <id_zona> <id_proc.regras> <id_regra>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="asoc"){
        if(argumentos.size()==3){
            try{
                int id_zona=stoi(argumentos[0]);
                char letra_proc=argumentos[1][0];
                int valor_inteiro_proc = stoi(argumentos[1].substr(1));
                char letra_aparelho = argumentos[2][0];
                int valor_inteiro_aparelho= stoi(argumentos[2].substr(1));
                infos << set_color(10) << "Comando valido\n";
                habitacao.AssociarProcAparelho(id_zona,valor_inteiro_proc,valor_inteiro_aparelho,infos);
            }catch (invalid_argument &){
                infos << set_color(4) << "Comando invalido!Digite asoc <id_zona> <id_proc.regras> <id_aparelho>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="ades"){
        if(argumentos.size()==3){
            try{
                int id_zona=stoi(argumentos[0]);
                char letra_proc=argumentos[1][0];
                int valor_inteiro_proc = stoi(argumentos[1].substr(1));
                char letra_aparelho = argumentos[2][0];
                int valor_inteiro_aparelho= stoi(argumentos[2].substr(1));
                infos << set_color(10) << "Comando valido\n";
                habitacao.DesassociarProcAparelho(id_zona,valor_inteiro_proc,valor_inteiro_aparelho,infos);
            }catch (invalid_argument &){
                infos << set_color(4) << "Comando invalido!Digite ades <id_zona> <id_proc.regras> <id_aparelho>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="acom"){
        if(argumentos.size()==3){
            try{
                int id_zona= stoi(argumentos[0]);
                char letra_aparelho=argumentos[1][0];
                int valor_inteiro_aparelho = stoi(argumentos[1].substr(1));
                string novo_comando=argumentos[2];
                infos << set_color(10) << "Comando valido\n";
                habitacao.EnviarcomandoAparelho(id_zona,valor_inteiro_aparelho,novo_comando,infos);
            }catch (invalid_argument &){
                infos << set_color(4) << "Comando invalido!Digite acom <id_zona> <id_aparelho> <comando>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="psalva"){
        if(argumentos.size()==3){
            try{
                int id_zona=stoi(argumentos[0]);
                char letra_proc=argumentos[1][0];
                int valor_inteiro_proc = stoi(argumentos[1].substr(1));
                string nome=argumentos[2];
                infos << set_color(10) << "Comando valido\n";
                habitacao.SalvaProc(id_zona,valor_inteiro_proc,nome,infos);
            }catch (invalid_argument &){
                infos << set_color(4) << "Comando invalido!Digite psalva <id_zona> <id_proc.regras> <nome>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="prepoe"){
        if(argumentos.size()==1){
            try {
                string nome=argumentos[0];
                infos << set_color(10) << "Comando valido\n";
                //hab

            }catch (invalid_argument &) {
                infos << set_color(4) << "Comando invalido!Digite prepoe <nome>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="prem"){
        if(argumentos.size()==1){
            try{
                string nome=argumentos[0];
                infos << set_color(10) << "Comando valido\n";
                habitacao.ApagarProcSalvo(nome,infos);
            }catch (invalid_argument &){
                infos << set_color(4) << "Comando invalido!Digite prem <nome>\n";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }


    else if(comando=="plista"){
        if(argumentos.size()==0){
            infos << set_color(10) << "Comando valido\n";
            habitacao.ListacopiasProc(infos);
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="exec"){
        if(argumentos.size()==1){
            try{
                string nome_fich=argumentos[0];
                infos << set_color(10) << "Comando valido\n";
                if(leFicheiro(nome_fich,infos)){
                    infos << set_color(10) << "Comando lido com sucesso\n";
                }

                else{
                    infos << set_color(4) << "Erro a abrir ficheiro\n";
                }
            }catch (invalid_argument &){
                infos << set_color(4) << "Comando invalido!Digite exec <nome_ficheiro>";
            }
        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else if(comando=="sair"){
        if(argumentos.size()==0){
            infos << set_color(10) << "Comando valido\n";
            infos << "Encerrar o programa";

        }
        else
            infos << set_color(4) << "Comando invalido\n";
    }

    else{
        infos << set_color(4) << "Comando desconhecido\n";
    }


}

bool Interacao::leFicheiro(const string &ficheiro, Window &infos) {
    std::ifstream arquivo(ficheiro);

    if (arquivo.is_open()) {
        string linha;

        while (std::getline(arquivo, linha)) {
            infos << linha << "\n";
            checkcomando(linha);

        }

        arquivo.close();

    } else {
        infos << set_color(4) << "Erro ao abrir o arquivo\n";
        return false;
    }
}

