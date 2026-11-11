#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H
#include <string>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include "ITransmisible.h"

class DispositivoComunicacion:public ITransmisible{
protected:
	std::string idDispositivoComunicacion;
	std::string tipoDispositivo;
	
public:
    
	DispositivoComunicacion(std::string _id, std::string _tipo);
	
	virtual ~DispositivoComunicacion() = default;
	
	std::string getId() const;
	std::string getTipo() const;
};

#endif

