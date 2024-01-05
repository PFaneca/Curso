//
// Created by ASUS on 01/11/2023.
//

#ifndef POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_ZONA_H
#define POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_ZONA_H
#include "Sensor.h"
#include "Aparelho.h"
#include "Processador.h"
#include "Propriedade.h"
#include "Terminal.h"
#include <map>
class Zona{
    int linha,coluna;
    int id_z;
    static int contador_z;
    vector <Sensor*>sensores;
    vector <Aparelho*>aparelhos;
    vector <Processador*>processadores;
    vector <Propriedade>propriedades;
    vector <Regra*>regras;
    vector<Processador*> processadoresSalvos;
public:
    Zona();
    ~Zona();
    int getId() const;
    string getString()const;


    void AdicionarPropriedade(const Propriedade &propriedade);
    void criarProp();
    void listarPropriedades(term::Window &infos)const;
    void modificarProp(const string &nome,double novovalor,term::Window &infos);

    void AdicionarSensor( Propriedade * prop,term::Window &infos);
    void RemoverSensor(int idsensor,term::Window &infos);
    void listarSensores(term::Window &infos)const;
    int getultimosensor()const;
    string getletraultimosensor()const;
    bool Sensorassociadoregra(int id_sensor)const;

    void AdicionarAparelhos(Aparelho *aparelho,term::Window &infos);
    void RemoverAparelho(int idaparelho,term::Window &infos);
    void listarAparelhos(term::Window &infos)const;
    Aparelho *encontraAparelho(int idAparelho);

    void AdicionarProcessador(Processador *proc);
    void RemoverProc(int idproc,term::Window &infos);
    void ListarProcessadores(term::Window &infos);
    bool mudarComandoProc(int idProc,string novoComando,term::Window &infos);

    void criarRegra(int idProc,const std::string &nomeRegra,int idSensor,double arg1,double arg2,term::Window &infos);
    void criarRegra(int idProc,const std::string &nomeRegra,int idSensor,double arg1,term::Window &infos);
    void listarRegras(int idProc,term::Window &infos);
    void removerRegra(int idproc,int idregra,term::Window &infos);
    void avaliaRegras(term::Window &infos);

    Processador *encontrarProcessador(int idProc);
    Sensor *encontrarSensor(int idSensor)const;
    void AssociarAparelho_Proc( int idProcessador, int idAparelho,term::Window &infos);
    void DesassociarAparelho_Proc(int idProcessador,int idAparelho,term::Window &infos);
    void enviarcomandoAparelho(int id_aparelho,string comando,term::Window &infos);


    int getNumeroSensores()const;
    int getNumeroAparalhos()const;
    int getNumeroProcessadores()const;

    void SalvaProc(int id_proc,string &nome,term::Window &infos);
    void Listacopiasproc(term::Window &infos);
    void ReporProcSalvo(string &nome,term::Window &infos);
    void ApagarProcSalvo(string nome,term::Window &infos);


    void AvancaInstante();

    void ExibirPropAlteradas(term::Window &infos);
};




#endif //POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_ZONA_H
