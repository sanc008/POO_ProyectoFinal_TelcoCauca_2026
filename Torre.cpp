#include "Torre.h"

Torre::Torre(int idTorre, const std::string& ubicacion, double alturaMetros):
    idTorre(idTorre), ubicacion(ubicacion), alturaMetros(alturaMetros){
	if(ubicacion.length()==0){
		throw std::invalid_argument("Se debe establecer una ubicacion para la torre");
	}
}
Torre::~Torre(){
	
}
