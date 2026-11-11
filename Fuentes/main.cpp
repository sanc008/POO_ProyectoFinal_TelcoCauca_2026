#include "Tecnico.h"
#include "Antena.h"
#include "Funciones.h"
#include "DispositivoComunicacion.h"
#include "GatewayLoRa.h"
#include "RouterWiFi.h"
#include <mutex>
#include <stdexcept>
#include <vector>



std::mutex mtx_consola;
void PorecesarTransmicion(DispositivoComunicacion*s){
	if(s==nullptr){
		throw std::invalid_argument("El obejto no existe");
	}
	std::lock_guard<std::mutex> lock(mtx_consola);
	s->transmitir();
}

int main (int argc, char *argv[]) {
	//Creacion del vector de dispositivos
	
	std::vector <DispositivoComunicacion*> red;
	red.push_back(new RouterWiFi("31231",2));
	
	//
red.push_back(nullptr);
   try{
	for(DispositivoComunicacion*s:red){
     s->transmitir();
   }
   }catch (const std::invalid_argument&e){
		std::cerr<<"[ERROR]"<<e.what();
   }
	   
	

		
	Tecnico santiago("SA", "sistemas");
	std::cout<<santiago;
	try{
	Antena a1(3123123,42,"5G");
	a1.asociarTecnico(&santiago);
	}catch (const std::invalid_argument& e){
		std::cerr<<"\n[ERROR]"<<e.what()<<"\n";
	}
	return 0;
}

