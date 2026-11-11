#include "Antena.h"

Antena::Antena(int idAntena, double frecuenciaMHz, const std::string& tecnologia):
idAntena(idAntena), frecuenciaMHz(frecuenciaMHz),tecnologia(tecnologia){
	if(tecnologia.length()==0){
		throw std::invalid_argument("Se tiene que establecer una tecnologia para la antena");
	}
}

Antena::~Antena(){
    
}
void Antena::asociarTecnico(Tecnico* s){
	if(s==nullptr){
		throw std::invalid_argument("No se puede asociar un tecnico Nullptr con la antena");
	}
	
	responsableMantenimiento=s;
}
