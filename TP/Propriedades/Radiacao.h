//
// Created by ASUS on 20/12/2023.
//

#ifndef TP_RADIACAO_H
#define TP_RADIACAO_H
#include "../Propriedade.h"

class Radicao : public Propriedade{


public:
    Radicao(): Propriedade("Radiacao",25,0,INFINITY," Becquerel"){}
};
#endif //TP_RADIACAO_H
