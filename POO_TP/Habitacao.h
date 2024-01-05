//
// Created by ASUS on 05/12/2023.
//

#ifndef TP_HABITACAO_H
#define TP_HABITACAO_H
#include <map>
#include <vector>
#include "Zona.h"
#include "Terminal.h"

class Habitacao{
    int numlinhas;
    int numcolunas;
    map<int,term::Window> mapWin;
    map<int,Zona>zonas;
    int instantes=0;

public:


    Habitacao();
    void criarhabitacao(int linhas,int colunas);
    ~Habitacao();
    void removerHabitacao();


    void criarzona(int linha,int coluna,term::Window &infos);
    void listarZonas(term::Window &infos);
    void removerzona(int id_zona,term::Window &info);

    void listarPropriedades(int id_zona,term::Window &infos);
    void modificarprop(int id_zona,const string &nome,double novovalor,term::Window &infos);

    void adicionaSensor(int id_zona, Propriedade *prop,term::Window &infos);
    void removerSensor(int id_zona,int idsensor,term::Window &infos);
    void ListarSensores(int id_zona,term::Window &infos)const;

    void AdicionaProc(int id_zona,Processador *proc,term::Window &info);
    void RemoverProc(int id_zona,int idproc,term::Window &infos);
    void ListarProcessadores(int id_zona,term::Window &infos);
    void mudarComandoProc(int if_zona,int id_proc,string novoComando,term::Window &infos);
    void AssociarProcAparelho(int id_zona,int id_proc,int id_aparelho,term::Window &infos);
    void DesassociarProcAparelho(int id_zona,int id_proc,int id_aparelho,term::Window &infos);


    void AdicionaAparelho(int id_zona,Aparelho *aparelho,term::Window &infos);
    void RemoverAparelho(int id_zona,int idaparelho,term::Window &infos);
    void ListarAparelhos(int id_zona,term::Window &infos);
    void EnviarcomandoAparelho(int id_zona,int id_aparelho,string comando,term::Window &infos);

    void criarRegra(int id_zona,int id_proc,const string &nomeRegra,int id_sensor,double arg1,double arg2,term::Window &infos);
    void criarRegra(int id_zona,int id_proc,const string &nomeRegra,int id_sensor,double arg1,term::Window &infos);
    void ListarRegras(int id_zona,int id_proc,term::Window &infos);
    void removerRegra(int id_zona,int id_proc,int id_regra,term::Window &infos);
    void AvaliaRegras();

    void SalvaProc(int id_zona,int id_proc,string &nome,term::Window &infos);
    void ReporProc(string &nome);
    void ListacopiasProc(term::Window &infos);
    void ApagarProcSalvo(string &nome,term::Window &infos);



    int getInstantes();
    void Prox(term::Window &infos);
    void Avanca(int n);
};


#endif //TP_HABITACAO_H
