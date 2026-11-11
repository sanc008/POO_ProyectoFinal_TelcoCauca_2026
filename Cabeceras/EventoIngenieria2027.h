#ifndef EVENTOINGENIERIA2027_H
#define EVENTOINGENIERIA2027_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
#include <thread>

class EventoIngenieria2027 {
private:
	std::string presentado_Por="santiago campo"; 
    std::vector <std::string > eventos;
	int eventosRegistrados;
	
public:
	EventoIngenieria2027();
	void registrarEvento(const std::string& evento);
	void mostrarEvento();

};

#endif

