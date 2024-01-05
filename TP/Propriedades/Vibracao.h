//
// Created by ASUS on 20/12/2023.
//

#ifndef TP_VIBRACAO_H
#define TP_VIBRACAO_H
#include "../Propriedade.h"

class Vibracao : public Propriedade{

public:
    Vibracao() : Propriedade("Vibracao",30,0,INFINITY," Hertz"){}
};
#endif //TP_VIBRACAO_H
