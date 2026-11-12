#include "ServidorCentral.h"
#include "ExcepcionSocket.h"
#include "TramaTelemetria.h"
#include <iostream>

// Inclusión de librerías POSIX (y compatibilidad para Zinjal/Windows)
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif


extern std::mutex mtx_consola; 

ServidorCentral::ServidorCentral(unsigned short pTCP, unsigned short pUDP) 
	: puertoTCP(pTCP), puertoUDP(pUDP), servidorActivo(false), socketTCP(SOCKET_INVALIDO), socketUDP(SOCKET_INVALIDO) {
}

ServidorCentral::~ServidorCentral() {
	detener();
}

void ServidorCentral::iniciar() {
	servidorActivo = true;
	
	// =========================================================
	// 1. INICIALIZACIÓN TCP (socket -> bind -> listen)
	// =========================================================
	socketTCP = socket(AF_INET, SOCK_STREAM, 0);
	if (socketTCP == SOCKET_INVALIDO) throw ExcepcionSocket("Fallo al crear socket TCP");
	
	sockaddr_in dirTCP{};
	dirTCP.sin_family = AF_INET;
	dirTCP.sin_addr.s_addr = INADDR_ANY;
	dirTCP.sin_port = htons(puertoTCP);
	
	if (bind(socketTCP, (struct sockaddr*)&dirTCP, sizeof(dirTCP)) < 0)
		throw ExcepcionSocket("Error en bind() TCP");
	
	if (listen(socketTCP, 5) < 0)
		throw ExcepcionSocket("Error en listen() TCP");
	
	// =========================================================
	// 2. INICIALIZACIÓN UDP (socket -> bind)
	// =========================================================
	socketUDP = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketUDP == SOCKET_INVALIDO) throw ExcepcionSocket("Fallo al crear socket UDP");
	
	sockaddr_in dirUDP{};
	dirUDP.sin_family = AF_INET;
	dirUDP.sin_addr.s_addr = INADDR_ANY;
	dirUDP.sin_port = htons(puertoUDP);
	
	if (bind(socketUDP, (struct sockaddr*)&dirUDP, sizeof(dirUDP)) < 0)
		throw ExcepcionSocket("Error en bind() UDP");
	

#ifdef _WIN32
	DWORD timeout = 3000; // milisegundos
	setsockopt(socketUDP, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
#else
	struct timeval tv{3, 0};
	setsockopt(socketUDP, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
#endif
	
	std::cout << "\n[Servidor] INICIADO -> TCP: " << puertoTCP << " | UDP: " << puertoUDP << "\n";
	
	// Lanzar hilos maestros
	hiloEscuchaTCP = std::thread(&ServidorCentral::aceptarConexionesTCP, this);
	hiloEscuchaUDP = std::thread(&ServidorCentral::recibirTelemetriaUDP, this);
}

void ServidorCentral::aceptarConexionesTCP() {
	int idCliente = 1;
	while (servidorActivo) {
		// accept() bloquea hasta que un cliente se conecte
		SocketNativo clienteSocket = accept(socketTCP, nullptr, nullptr);
		
		if (clienteSocket != SOCKET_INVALIDO) {
			std::lock_guard<std::mutex> lock(mtx_consola);
			std::cout << "[TCP] Cliente remoto " << idCliente << " conectado exitosamente.\n";
			
			// Hilo dedicado por cliente
			std::thread hiloCliente(&ServidorCentral::atenderClienteTCP, this, clienteSocket, idCliente);
			hiloCliente.detach(); // Se saca del hilo principal para tener varios a la vez
			idCliente++;
		}
	}
}

void ServidorCentral::atenderClienteTCP(SocketNativo clienteSocket, int idCliente) {
	char buffer[256];
	
	int bytesLeidos = recv(clienteSocket, buffer, sizeof(buffer) - 1, 0);
	
	if (bytesLeidos > 0) {
		buffer[bytesLeidos] = '\0';
		std::lock_guard<std::mutex> lock(mtx_consola);
		std::cout << "[TCP RX - Cliente " << idCliente << "] " << buffer << "\n";
	}
	
#ifdef _WIN32
	closesocket(clienteSocket);
#else
	close(clienteSocket);
#endif
}

void ServidorCentral::recibirTelemetriaUDP() {
	while (servidorActivo) {
		TramaTelemetria tramaRecibida;
		sockaddr_in cli_addr{};
		socklen_t len = sizeof(cli_addr);
		

		int bytes = recvfrom(socketUDP, reinterpret_cast<char*>(&tramaRecibida), sizeof(tramaRecibida), 0, (sockaddr*)&cli_addr, &len);
		
		if (bytes == sizeof(TramaTelemetria)) {
			std::lock_guard<std::mutex> lock(mtx_consola);
			std::cout << "[UDP RX] Estacion: " << tramaRecibida.idEstacion 
				<< " | Temp: " << tramaRecibida.temperatura << " C\n";
		} 
		else if (bytes < 0) {
			// Manejo de Timeout Defensivo
			std::lock_guard<std::mutex> lock(mtx_consola);

		}
	}
}

void ServidorCentral::detener() {
	servidorActivo = false;
#ifdef _WIN32
	closesocket(socketTCP);
	closesocket(socketUDP);
#else
	close(socketTCP);
	close(socketUDP);
#endif
	
	if (hiloEscuchaTCP.joinable()) hiloEscuchaTCP.join();
	if (hiloEscuchaUDP.joinable()) hiloEscuchaUDP.join();
}
