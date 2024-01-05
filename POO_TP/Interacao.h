//
// Created by ASUS on 13/12/2023.
//

#ifndef TP_INTERACAO_H
#define TP_INTERACAO_H
#include "Habitacao.h"
#include "Terminal.h"
#include "Propriedades/Temperatura.h"
#include "Propriedades/Fumo.h"
#include "Propriedades/Humidade.h"
#include "Propriedades/Luz.h"
#include "Propriedades/Radiacao.h"
#include "Propriedades/Som.h"
#include "Propriedades/Vibracao.h"
#include "Aparelhos/Aquecedor.h"
#include "Aparelhos/Aspersor.h"
#include "Aparelhos/Lampada.h"
#include "Aparelhos/Refrigerador.h"
#include "map"
#include <iomanip>
#include "Terminal.h"
using namespace term;
using namespace std;
class Interacao{
    Habitacao habitacao;
    Window cmd;
    Window infos;
    static const std::map<std::string, int> comandos;


public:
    Interacao();
     int leComando ();
    void checkcomando(string frase);
    bool leFicheiro(const string &ficheiro,Window &infos);


   // bool executahabitacao(std::istringstream &restolinha);
};

#endif //TP_INTERACAO_H
