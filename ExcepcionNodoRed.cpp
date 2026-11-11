#include "ExcepcionNodoRed.h"

ExcepcionNodoRed::ExcepcionNodoRed(const std::string& errorPropio):
	std::runtime_error("[ERROR DE NODO]"+errorPropio){
	
}

ExcepcionNodoRed::~ExcepcionNodoRed(){
	
}

