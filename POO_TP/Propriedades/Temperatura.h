//
// Created by ASUS on 04/12/2023.
//

#ifndef TP_TEMPERATURA_H
#define TP_TEMPERATURA_H


#include "../Propriedade.h"

class Temperatura : public Propriedade{


public:
    Temperatura() : Propriedade("Temperatura", 10, -273.15, INFINITY, " graus celsius") {}
};


#endif //TP_TEMPERATURA_H
