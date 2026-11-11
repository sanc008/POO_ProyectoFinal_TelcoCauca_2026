#include "DispositivoRed.h"

DispositivoRed::DispositivoRed(const std::string& direccionIP,	const std::string& direccionMAC, bool estadoOperativo):
  direccionIP(direccionIP), direccionMAC(direccionMAC), estadoOperativo(estadoOperativo)  {
	if (direccionIP.length()==0){
    throw std::invalid_argument("[No se ha asignado niguna ip]");
  }
  if (direccionMAC.length()==0){
    throw std::invalid_argument("[No se ha asignado ninguna direccion MAC]");
  }
}

DispositivoRed::~DispositivoRed(){

}
