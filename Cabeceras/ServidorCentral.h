#ifndef SERVIDORCENTRAL_H
#define SERVIDORCENTRAL_H

#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <stdexcept>

// Bloque de compatibilidad para Sockets en Zinjal (Windows)
#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET SocketNativo;
#define SOCKET_INVALIDO INVALID_SOCKET
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
typedef int SocketNativo;
#define SOCKET_INVALIDO -1
#endif

class ServidorCentral {
private:
	unsigned short puertoTCP;
	unsigned short puertoUDP;
	
	
	SocketNativo socketTCP;
	SocketNativo socketUDP;
	
	// Hilos maestros 
	std::thread hiloEscuchaTCP;
	std::thread hiloEscuchaUDP;
	
	bool servidorActivo;
	
	
	// Métodos privados que ejecutarán los hilos

	// Bucle para TCP: ejecuta accept() y lanza un hilo por cliente
	void aceptarConexionesTCP();
	
	// Atiende a un cliente TCP específico de forma concurrente
	void atenderClienteTCP(SocketNativo clienteSocket, int idCliente);
	
	// Bucle para UDP: escucha datagramas de sensores con recvfrom()
	void recibirTelemetriaUDP();
	
public:
	// Constructor y Destructor
	ServidorCentral(unsigned short pTCP, unsigned short pUDP);
	~ServidorCentral();
	
	// Arranca los sockets (socket, bind, listen) y lanza los hilos maestros
	void iniciar();
	
	// Cierra de forma segura las conexiones y une los hilos (join)
	void detener();
	
	// Evitar copias accidentales del servidor (Regla de POO para recursos)
	ServidorCentral(const ServidorCentral&) = delete;
	ServidorCentral& operator=(const ServidorCentral&) = delete;
};

#endif
