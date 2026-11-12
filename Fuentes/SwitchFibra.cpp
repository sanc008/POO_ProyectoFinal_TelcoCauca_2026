#include "SwitchFibra.h"

SwitchFibra::SwitchFibra(std::string _id, std::string _tipo, int _puertos):DispositivoComunicacion(_id, _tipo),puertosActivos(_puertos) {
	
}

SwitchFibra::~SwitchFibra() {
	
}

void SwitchFibra::transmitir ( ) {
	std::cout<<" [Switch "<<idDispositivoComunicacion<<"]"<<"Conexion exitosa";
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

