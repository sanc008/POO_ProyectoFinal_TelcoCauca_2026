#ifndef ANTENA_H
#define ANTENA_H
#include <string>
#include <iostream>
#include <stdexcept>

class Tecnico;

class Antena {
private:
	int idAntena;
	double frecuenciaMHz;
	std::string tecnologia;
	Tecnico* responsableMantenimiento;

	
public:
	Antena(int idAntena, double frecuenciaMHz, const std::string& tecnologia);
	~Antena();
	void asociarTecnico(Tecnico* s);

};

#endif
