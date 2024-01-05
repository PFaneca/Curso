//
// Created by ASUS on 05/12/2023.
//

#ifndef TP_MAIOR_H
#define TP_MAIOR_H
#include "../Regra.h"

class Regra_Maior : public Regra{
    double valorComparacao;
public:
    Regra_Maior(Sensor &sensor,double valorComparacao);
    ~Regra_Maior();
    Regra * duplica()const override;
    string getString()const;
    double getvalor();
    bool verificar();
};


#endif //TP_MAIOR_H
