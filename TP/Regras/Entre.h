//
// Created by ASUS on 05/12/2023.
//

#ifndef TP_ENTRE_H
#define TP_ENTRE_H
#include "../Regra.h"

class Regra_entre : public Regra{
    double valor1,valor2;
public:
    Regra_entre(Sensor &sensor,double valor1,double valor2);
    Regra * duplica()const override;
    ~Regra_entre();
    string getString()const;
    bool verificar();
};




#endif //TP_ENTRE_H
