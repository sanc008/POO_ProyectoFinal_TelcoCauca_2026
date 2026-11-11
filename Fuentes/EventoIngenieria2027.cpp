#include "EventoIngenieria2027.h"

EventoIngenieria2027::EventoIngenieria2027() {
	this->eventosRegistrados=0;
}

void EventoIngenieria2027::registrarEvento(const std::string& evento){
	eventosRegistrados++;
	eventos.push_back(evento);
    std::cout<<"[Evento N"<<eventosRegistrados<<"] registrado con exito\n";
	
}
void EventoIngenieria2027::mostrarEvento(){
	int i=1;
		for(const std::string& evento:eventos){
		std::cout<<"[EVENTO N"<<i<<"] "<<evento<<"\n";
		++i;
	}


}
