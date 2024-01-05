//
// Created by ASUS on 14/11/2023.
//

#ifndef POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_APARELHO_H
#define POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_APARELHO_H
#include "Propriedade.h"
#include "Sensor.h"
#include "utils.h"

#include "Terminal.h"


class Aparelho{
    string nome;
    string tipo;
    string letraMaiuscula="A";
    string letra="a";
    string comando;
    string efeito;
    int id;
    static int contador;
    bool ligado;
    int instante_ligado;




    vector<Sensor*>sensores;
    vector<Propriedade*>propriedades;


public:
    Aparelho(string tipo,string nome);
    virtual ~Aparelho();

    string getletra();
    string gettipo();
    string getletraMaiuscula()const;
    string getnome()const;
    virtual string getString()const;
    string getComando()const;
    bool getbool();
    void AtualizarComando(const std::string& novoComando, term::Window& infos);

    int getId()const;

     void ligar();
     void desligar();
     virtual void aoLigar();
     virtual void aoDesligar();
    Sensor *encontrarsensorProp(const std::string& nomePropriedade);
    void AssociaSensor(Sensor *sensor);
    const vector<Propriedade*> &props();
    void AdicionarPropriedade(Propriedade &prop);
    void exibirprop(term::Window &infos);
    Propriedade* getPropriedade(const std::string& tipo);

    int getInstanteAtual();
    int getInstanteLigado();
};
#endif //POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_APARELHO_H
