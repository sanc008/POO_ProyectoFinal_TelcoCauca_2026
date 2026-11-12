#ifndef TORRE_H
#define TORRE_H
#include <string>
#include <vector>
#include <stdexcept>
#include <ostream>

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
	void agregarAntena(Antena*s);
	friend std::ostream&operator<<(std::ostream&t, const Torre&tor);

};

#endif


