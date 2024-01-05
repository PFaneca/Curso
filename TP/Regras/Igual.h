//
// Created by ASUS on 27/12/2023.
//

#ifndef TP_IGUAL_H
#define TP_IGUAL_H
#include "../Regra.h"

class Regra_Igual : public Regra{
    double valor1;
public:
    Regra_Igual(Sensor &sensor,double valor);
    ~Regra_Igual();
    Regra * duplica()const override;
    string getString()const;
    bool verificar();
};

#endif //TP_IGUAL_H
