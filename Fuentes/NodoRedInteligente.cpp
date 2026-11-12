#include "NodoRedInteligente.h"

NodoRedInteligente::NodoRedInteligente(const std::string& direccionIP,	const std::string& direccionMAC, bool estadoOperativo,
									   const std::string& tipoSensor, double valorLectura,int idNodo, int paquetes):
	
    DispositivoRed(direccionIP,direccionMAC, estadoOperativo), SensorIoT(tipoSensor, valorLectura),idNodo(idNodo), paquetes(paquetes){
	
}


NodoRedInteligente::~NodoRedInteligente(){
    
}


std::ostream&operator<<(std::ostream&z, const NodoRedInteligente&n) {
    
    z<<"\n================Nodo Red Inteligente================"
        <<"\n[Direccion IP del Nodo] "<<n.direccionIP 
        <<"\n[Direccion MAC] "<<n.direccionMAC
        <<"\n[Estado operativo] "<<n.estadoOperativo<<"\n"
        <<"====================================================\n";
        return z;
}

NodoRedInteligente NodoRedInteligente::operator +(const NodoRedInteligente&n2)const{
	if(this->tipoSensor!=n2.tipoSensor){
	throw std::invalid_argument("Los tipos de sensor deben ser iguales");
}
	return NodoRedInteligente(direccionIP,direccionMAC, estadoOperativo,tipoSensor, valorLectura,idNodo, paquetes);
}




