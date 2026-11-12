#include "Torre.h"

Torre::Torre(int idTorre, const std::string& ubicacion, double alturaMetros):
    idTorre(idTorre), ubicacion(ubicacion), alturaMetros(alturaMetros){
	if(ubicacion.length()==0){
		throw std::invalid_argument("Se debe establecer una ubicacion para la torre");
	}
}
Torre::~Torre(){
}


void Torre::agregarAntena(Antena*s){
	if (s==nullptr){
		throw std::invalid_argument("[No se puede asociar una antena nula]\n");
	}
	listaAntenas.push_back(s);
}
std::ostream&operator<<(std::ostream&t, const Torre& tor){
	t<<"\n============Info. Torre============\n"
		<<"\n[ID Torre] "<<tor.idTorre
		<<"\n[Ubicacion] "<<tor.ubicacion
		<<"\n[ID Altura] "<<tor.alturaMetros
		<<"\n[N. Antenas]"<<tor.listaAntenas.size()
		<<"\n\n====================================\n\n";
	return t;
}
