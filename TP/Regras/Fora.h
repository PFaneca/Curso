//
// Created by ASUS on 29/12/2023.
//

#ifndef TP_FORA_H
#define TP_FORA_H

#endif //TP_FORA_H
#include "../Regra.h"

class Regra_Fora : public Regra{
    double valor1,valor2;

public:
    Regra_Fora(Sensor &sensor,double valor1,double valor2);
    Regra * duplica()const override;
    ~Regra_Fora();
    string getString()const;
    bool verificar();
};