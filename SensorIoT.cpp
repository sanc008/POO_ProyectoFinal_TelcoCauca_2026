#include "SensorIoT.h"


SensorIoT::SensorIoT(const std::string& tipoSensor, double valorLectura):
    tipoSensor(tipoSensor), valorLectura(valorLectura){
    if(valorLectura<-50.0||valorLectura>100.0){
		throw std::out_of_range("La lectura esta fuera de rango");
	}

}

SensorIoT::~SensorIoT(){

}
