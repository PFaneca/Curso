//
// Created by ASUS on 01/11/2023.
//

#ifndef POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_PROPRIEDADE_H
#define POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_PROPRIEDADE_H
#include "utils.h"

class Propriedade{
    string tipo;
    string unidade;
    double valor;
    double valor_min;
    double valor_max;

public:
    Propriedade(string nome, double val, double val_min, double val_max,string unidade);
    Propriedade(const Propriedade &outro);
    string gettipo()const;
    string getunidade()const;
    double getvalor()const;
    bool setvalor(double novovalor);
    void subvalor(double valorSubtrair);
    void addvalor(double valorAdicionar);
    string getString()const;
};





#endif //POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_PROPRIEDADE_H
