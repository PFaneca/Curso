//
// Created by ASUS on 27/12/2023.
//

#ifndef TP_MENOR_H
#define TP_MENOR_H

#include "../Regra.h"

class Regra_Menor : public Regra{
    double valor;

public:
    Regra_Menor(Sensor &sensor,double valor);
    ~Regra_Menor();
    Regra * duplica()const override;
    string getString()const;
    bool verificar();
};

#endif //TP_MENOR_H
