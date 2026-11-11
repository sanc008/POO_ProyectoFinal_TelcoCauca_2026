#include "DispositivoComunicacion.h"

DispositivoComunicacion::DispositivoComunicacion(std::string _id, std::string _tipo):idDispositivoComunicacion(_id), tipoDispositivo(_tipo) {
	if(idDispositivoComunicacion.length()==0){
		throw std::invalid_argument("[Se debe asiganar un ID al dispositivo de comunicacion]");
	}if(tipoDispositivo.length()==0){
		throw std::invalid_argument("[Se debe asignar un tipo al dispositivo de comunicacion]");
	}
}


std::string DispositivoComunicacion::getId() const { 
	return idDispositivoComunicacion; 
}
std::string DispositivoComunicacion::getTipo() const {
	return tipoDispositivo; 
}

