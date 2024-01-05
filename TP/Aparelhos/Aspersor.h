//
// Created by ASUS on 31/12/2023.
//

#ifndef TP_ASPERSOR_H
#define TP_ASPERSOR_H
#include "../Aparelho.h"
class Aspersor : public Aparelho{


public:
    Aspersor();
    ~Aspersor();
    string getString()const;



    void aoLigar();
    void aoDesligar();
};

#endif //TP_ASPERSOR_H
