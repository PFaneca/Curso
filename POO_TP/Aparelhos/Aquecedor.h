//
// Created by ASUS on 08/12/2023.
//

#ifndef TP_AQUECEDOR_H
#define TP_AQUECEDOR_H
#include "../Aparelho.h"
#include "../Propriedade.h"
#include "../Propriedades/Temperatura.h"

class Aquecedor:public Aparelho{

    int ultimoaumentoTemperatura=0;
public:
    Aquecedor();
    ~Aquecedor();
    string getString()const;
    //void ligar();
    Sensor *encontrarsensorProp(const std::string& nomePropriedade);



    void aoLigar();
    void aoDesligar();


};
#endif //TP_AQUECEDOR_H
