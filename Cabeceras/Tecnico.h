#ifndef TECNICO_H
#define TECNICO_H
#include <string>
#include <iostream>
#include <stdexcept>
#include <ostream>

class Tecnico {
private:
	int idAntena;
	std::string nombre;
	std::string especialidad;
		
	public:
	Tecnico(const std::string& name, const std::string& specialty);
	void mostrarInformacion();
	int getIdAntena();
	std::string getNombre();
	std::string getEspecialidad();
	void setEspecialidad(const std::string& especialidad);
	void setIdAntena(int id);
	//Funciones sobrecargadas para el tecnico
	friend std::ostream&operator<<(std::ostream&tec, const Tecnico&t);
	
};

#endif

