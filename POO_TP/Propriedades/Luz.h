//
// Created by ASUS on 20/12/2023.
//

#ifndef TP_LUZ_H
#define TP_LUZ_H
#include "../Propriedade.h"
class Luz : public Propriedade {


public:
    Luz() : Propriedade("Luz",40,0,INFINITY," Lumens"){}
};
#endif //TP_LUZ_H
