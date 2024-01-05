//
// Created by ASUS on 08/11/2023.
//

#ifndef POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_SENSOR_H
#define POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_SENSOR_H
#include <vector>
#include "utils.h"
#include "Propriedade.h"

class Sensor{
    string tipo="s";
    int id;
    static int contador;
    Propriedade *propriedade;
public:
    //Sensor(string zona,string chave);
    Sensor(Propriedade *propriedade) : propriedade(propriedade)  {id=++contador;}
    ~Sensor(){delete propriedade;}
    string letra()const;
    int getId()const;
    string getString()const;
    void realizarLeitura();
    double getvalor_prop();
    double setvalor_prop(double novo_valor);
    string getunidade();
    string gettipo()const;





};


#endif //POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_SENSOR_H
