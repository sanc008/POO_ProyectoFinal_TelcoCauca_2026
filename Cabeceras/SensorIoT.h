#ifndef SENSORIOT_H
#define SENSORIOT_H
#include <string>
#include <stdexcept>

class SensorIoT {
protected:
	std::string tipoSensor;
	double valorLectura;

public:
	SensorIoT(const std::string& tipoSensor, double valorLectura);
	virtual ~SensorIoT();
};

#endif

