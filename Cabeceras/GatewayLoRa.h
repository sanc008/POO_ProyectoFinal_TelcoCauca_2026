#ifndef GATEWAYLORA_H
#define GATEWAYLORA_H
#include "DispositivoComunicacion.h"

class GatewayLoRa:public DispositivoComunicacion {
private:
	float frecuenciaMHz;
public:
	GatewayLoRa(std::string _id, float _freq);
	void transmitir()override;
};

#endif

