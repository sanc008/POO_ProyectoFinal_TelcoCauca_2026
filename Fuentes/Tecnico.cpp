#include "Tecnico.h"

Tecnico::Tecnico(const std::string& name, const std::string& specialty)
	:nombre(name), especialidad(specialty){
	if (nombre.length()==0){
		throw std::invalid_argument("No puede registar a un tecnico sin nombre");
	}	
}

void Tecnico::mostrarInformacion(){
	
	
	
}
std::ostream&operator<<(std::ostream&tec, const Tecnico& t){
	tec<<"\n============Info. Tecnico============\n"
		<<"\n[Nombre] "<<t.nombre
	    <<"\n[Especialidad] "<<t.especialidad
		<<"\n[ID Antena asociada] "<<t.idAntena
		<<"\n\n====================================\n\n";
	return tec;

}
std::string Tecnico::getEspecialidad(){
	return especialidad;
}

int Tecnico::getIdAntena(){
	return idAntena;
}

std::string Tecnico::getNombre(){
	return nombre;
}

void Tecnico::setEspecialidad(const std::string& esp){
	this->especialidad=esp;
}

void Tecnico::setIdAntena(int id){
	this->idAntena=id;
}
