#ifndef TORRE_H
#define TORRE_H
#include <string>
#include <vector>
#include <stdexcept>

class Antena;

class Torre {
private:
	int idTorre;
	std::string ubicacion;
	double alturaMetros;
	std::vector <Antena*>listaAntenas;
	
	public:
	Torre(int idTorre, const std::string& ubicacion, double alturaMetros);
	~Torre();

};

#endif


