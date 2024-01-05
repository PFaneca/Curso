//
// Created by ASUS on 15/11/2023.
//

#ifndef POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_REGRA_H
#define POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_REGRA_H
#include "utils.h"
#include "Sensor.h"
class Regra{
    string descricao;
    string tipo="r";
    int id;
    static int contador;
    Sensor *sensorassociado;

public:
    Regra(Sensor &sensor,string descricao);
    virtual Regra *duplica() const=0;
    virtual ~Regra();
    int getId()const;
    string gettipo()const;
    string getDescricao()const;
    virtual string getString()const;
    Sensor *getSensorAssociado()const;
    double getSensor();
    virtual bool verificar();
    bool contemSensor(int id_sensor)const;



};

#endif //POO_2324_M1_MARTIMANTUNES_2022141890_PEDROFANECA_2022134142_REGRA_H
