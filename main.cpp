#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <stdexcept>
#include <string>

// Cabeceras exactas
#include "Tecnico.h"
#include "Antena.h"
#include "Torre.h"
#include "NodoRedInteligente.h"
#include "ExcepcionNodoRed.h"
#include "DispositivoComunicacion.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
#include "EventoIngenieria2027.h"

// Cabeceras Servidor
#include "ServidorCentral.h"
#include "TramaTelemetria.h"
#include "ExcepcionSocket.h"

#ifdef _WIN32
#include <winsock2.h>
#endif

// Mutex global
std::mutex mtx_consola;


void procesarDispositivo(DispositivoComunicacion* dev) {
	try {
		if (dev == nullptr) {
			throw std::invalid_argument("[INVALID ARGUMENT] Puntero nulo detectado.");
		}
		
		{
			std::lock_guard<std::mutex> lock(mtx_consola);
			std::cout << "\n[HILO " << std::this_thread::get_id() << "] Iniciando transmision...\n";
		}
		
		// Se ejecuta SIN retener mtx_consola para no bloquear al ServidorCentral
		dev->transmitir();
		
	} 
	catch (const std::exception& e) {
		std::lock_guard<std::mutex> lock(mtx_consola);
		std::cerr << "\n[HILO " << std::this_thread::get_id() << " - ERROR]: " << e.what() << "\n";
	}
}

void ejecutarHiloEventos(EventoIngenieria2027* evento) {
	
	if (evento != nullptr) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::lock_guard<std::mutex> lock(mtx_consola);
		std::cout<<"\n[HILO "<<std::this_thread::get_id()<<" ]";
		evento->mostrarEvento();
		
	}
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
	// Inicializacion obligatoria de Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "[Error] No se pudo inicializar Winsock.\n";
		return 1;
	}
#endif
	
	// =====================================================
	// PARTE 1: INFRAESTRUCTURA FÕSICA
	// =====================================================
	std::cout << "--- PARTE 1: INFRAESTRUCTURA FISICA ---\n";
	
	// Tecnicos
	Tecnico tecnico1("Manuel Castrillon", "Redes Digitales");
	Tecnico tecnico2("Esteban Gomez", "Mantenimeinto");
	
	std::cout << tecnico1 << tecnico2;
	
	// Torre
	Torre torrePrincipal(1, "Popayan - La Torre", 45.0);
	
	// Antenas
	Antena antena1(101, 350.0, "5G");
	Antena antena2(102, 190.0, "4G");
	
	antena1.asociarTecnico(&tecnico1);
	antena2.asociarTecnico(&tecnico2);
	
	Antena*nula(nullptr);
	
	// Torre
	try{
		torrePrincipal.agregarAntena(&antena1);
		torrePrincipal.agregarAntena(&antena2);
		torrePrincipal.agregarAntena(nula);
	}catch(const std::invalid_argument&e ){
		std::cerr<<"[ERROR TORRE] "<<e.what();
	}
	
	// =====================================================
	// PARTE 2: NODO DE RED INTELIGENTE
	// =====================================================
	std::cout << "\n--- PARTE 2: NODO DE RED INTELIGENTE ---\n";
	
	try {
		NodoRedInteligente nodo1("192.168.1.20", "AA:BB:CC", true, "Temperatura", 35.5, 1, 40);
		NodoRedInteligente nodo2("192.168.1.21", "AA:BB:DD", true, "Temperatura", 60.0, 2, 25);
		
		std::cout << nodo1 << nodo2;
		
		NodoRedInteligente nodoSumado = nodo1 + nodo2;
		std::cout << "\n> Resultado suma:\n" << nodoSumado;
		
		NodoRedInteligente nodoError1("192.168.1.22", "MAC", true, "Presion", 120.0, 3, 10);
	} catch (const ExcepcionNodoRed& e) {
		std::cerr << "[ExcepcionNodoRed] " << e.what() << "\n";
	}catch(const std::exception&e){
		std::cerr<<"[ERROR NODO]"<<e.what()<<"\n";
	}
	
	// =====================================================
	// MODULO 5: ARRANQUE DEL SERVIDOR CENTRAL
	// =====================================================
	std::cout << "\n--- INICIALIZANDO RED ---\n";
	std::cout << "Tamano de TramaTelemetria: " << sizeof(TramaTelemetria) << " bytes\n";
	ServidorCentral servidor(8080, 8081);
	try {
		servidor.iniciar();
	} catch (const ExcepcionSocket& e) {
		std::cerr << "[ERROR SERVIDOR]: " << e.what() << "\n";
	}
	// Pausa para dar tiempo a los puertos a abrirse
	std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
	
	// =====================================================
	// PARTE 3: POLIMORFISMO Y MULTIHILO
	// =====================================================
	std::cout << "\n--- PARTE 3: SUPERVISION EN HILOS ---\n";
	//Vector de red
	std::vector<DispositivoComunicacion*> red;
	
	//Instancia de dispositivos de red
	try{
		red.push_back(new SwitchFibra("SW-01","Switch", 24)); 
		red.push_back(new RouterWiFi("Router-01", 23)); 
		red.push_back(new GatewayLoRa("GW-01", 914.0)); 
		red.push_back(nullptr); 
	}catch (const std::exception&e){
		std::cerr<<"[ERROR RED] "<<e.what();
	}
	
	std::vector<std::thread> hilosRed;
	
	for (size_t i = 0; i < red.size(); ++i) {
		hilosRed.push_back(std::thread(procesarDispositivo, red[i]));
	}
	
	// ORDEN SECUENCIAL: Esperamos a que terminen los hilos de red ANTES de pasar a los eventos
	for (auto& hilo : hilosRed) {
		if (hilo.joinable()) {
			hilo.join();
		}
	}
	
	// =====================================================
	// PARTE 4: EVENTOS DE INGENIERIA 2027
	// =====================================================
	std::cout << "\n--- PARTE 4: EVENTOS DE INGENIERIA ---\n";
	//Eventos ingenieria
	EventoIngenieria2027 misEventos;
	misEventos.registrarEvento("NVIDIA GTC 2027");
	misEventos.registrarEvento("ITW Global 2027");
	misEventos.registrarEvento("Conecta Latam 2027");
	
	//Hilo eventos
	std::thread hiloEventos(ejecutarHiloEventos, &misEventos );
	
	if (hiloEventos.joinable()) {
		hiloEventos.join();
	}
	
	// =====================================================
	// FINALIZACI”N Y LIMPIEZA
	// =====================================================
	//Liberacion de memoria segura
	for (auto& dev : red) {
		if (dev != nullptr) {
			delete dev; 
			dev = nullptr; 
		}
	}
	red.clear();
	
	// Apagar sockets
	servidor.detener();
	
#ifdef _WIN32
	WSACleanup();
#endif
	
	return 0;
}
