//
// Created by ASUS on 20/12/2023.
//

#ifndef TP_HUMIDADE_H
#define TP_HUMIDADE_H
#include "../Propriedade.h"
class Humidade : public Propriedade{


public:
    Humidade() : Propriedade("Humidade",20,0,100,"%"){}
};
#endif //TP_HUMIDADE_H
