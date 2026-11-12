#ifndef SWITCHFIBRA_H
#define SWITCHFIBRA_H
#include "DispositivoComunicacion.h"

class SwitchFibra : public DispositivoComunicacion {
private:
	int puertosActivos;
	
public:
	SwitchFibra(std::string _id, std::string _tipo, int puertosActivos);
	virtual ~SwitchFibra() = default;
	void transmitir ( ) override;

};

#endif

