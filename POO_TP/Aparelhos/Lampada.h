//
// Created by ASUS on 31/12/2023.
//

#ifndef TP_LAMPADA_H
#define TP_LAMPADA_H

#include "../Aparelho.h"

class Lampada : public Aparelho{

public:
    Lampada();
    ~Lampada();
    string getString()const;



    void aoLigar();
    void aoDesligar();
};
#endif //TP_LAMPADA_H
