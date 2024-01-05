//
// Created by ASUS on 15/11/2023.
//

#ifndef POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_PROCESSADOR_H
#define POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_PROCESSADOR_H
#include "utils.h"
#include <vector>
#include <map>
#include "Regra.h"
#include "Aparelho.h"
#include "Terminal.h"

class Processador{
    string letra="p";
    int id;
    static int contador;
    vector <Regra*> regras;
    Aparelho *aparelho;
    vector <Aparelho*>aparelhos;
    string comandoProc;
    string nome;

public:
    Processador(string comando) : comandoProc(comando),aparelho(nullptr) {id=++contador;};
    Processador(const Processador & outro);
    Processador &operator=(const Processador &orig);
    ~Processador();
    int getId()const;
    string getString()const;
    string getletra()const;
    void AdicionarRegra(Regra *regra);
    bool RemoverRegra(int idregra);
    void ListarRegras(term::Window &infos);
    int contaRegras();
    string getComando();
    void setComando(const string &novoComando);
    bool avaliaRegras();
    Aparelho* getAparelhoAssociado() const;
    //const std::vector<Aparelho*> & getAparelhosAssociados() const;
    const std::vector<Regra*>& getRegras() const;
    void associarAparelho(Aparelho* novoAparelho);
    void removerAssociacaoAparelho();
    void alterarestado(bool ligado);
    string getnome();
    void setNome(const string& novoNome);
};


#endif //POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_PROCESSADOR_H
