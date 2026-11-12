#include "GatewayLoRa.h"

GatewayLoRa::GatewayLoRa(std::string _id, float _freq):DispositivoComunicacion(_id, "Gateway LoRaWAN"), frecuenciaMHz(_freq){
	
}

void GatewayLoRa::transmitir(){
	std::cout<<"[GatewayLoRa "<<idDispositivoComunicacion<<"]"<<"Enlace correcto";

	std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
