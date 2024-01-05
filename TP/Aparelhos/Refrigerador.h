//
// Created by ASUS on 31/12/2023.
//

#ifndef TP_REFRIGERADOR_H
#define TP_REFRIGERADOR_H

#include "../Aparelho.h"

class Refrigerador : public Aparelho {

public:
    Refrigerador();
    ~Refrigerador();
    string getString()const;



    void aoLigar();
    void aoDesligar();
};
#endif //TP_REFRIGERADOR_H
