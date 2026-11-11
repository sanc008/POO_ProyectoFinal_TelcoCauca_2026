#ifndef NODOREDINTELIGENTE_H
#define NODOREDINTELIGENTE_H
#include <ostream>
#include <stdexcept>
#include "DispositivoRed.h"
#include "SensorIoT.h"

class NodoRedInteligente:public DispositivoRed, public SensorIoT {
private:
	int idNodo, paquetes;
public:
	NodoRedInteligente(const std::string& direccionIP,	const std::string& direccionMAC, bool estadoOperativo,const std::string& tipoSensor, double valorLectura,int idNodo, int paquetes);
	~NodoRedInteligente();
	
	//Funciones sobrecargadas para NODO RED
	friend std::ostream& operator <<(std::ostream&z, const NodoRedInteligente&n) ;
	NodoRedInteligente operator +(const NodoRedInteligente&n2)const;
	
};

#endif
