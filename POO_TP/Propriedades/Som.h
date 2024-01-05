//
// Created by ASUS on 23/12/2023.
//

#ifndef TP_SOM_H
#define TP_SOM_H
#include "../Propriedade.h"

class Som : public Propriedade{

public:
    Som() : Propriedade("Som",100,0,INFINITY," Decibeis"){}
};
#endif //TP_SOM_H
