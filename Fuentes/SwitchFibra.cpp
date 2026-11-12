#include "SwitchFibra.h"
#include "ExcepcionSocket.h"
#include <iostream>
#include <string>
#include <cstring>
#include <mutex>

extern std::mutex mtx_consola;

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET SocketNativo;
#define SOCKET_INVALIDO INVALID_SOCKET
extern "C" WINSOCK_API_LINKAGE INT WSAAPI inet_pton(INT Family, PCSTR pszAddrString, PVOID pAddrBuf);
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int SocketNativo;
#define SOCKET_INVALIDO -1
#endif

SwitchFibra::SwitchFibra(std::string _id, std::string _tipo, int _puertos)
	: DispositivoComunicacion(_id, _tipo), puertosActivos(_puertos) {
}

void SwitchFibra::transmitir() {
	SocketNativo clienteTCP = socket(AF_INET, SOCK_STREAM, 0);
	if (clienteTCP == SOCKET_INVALIDO) {
		throw ExcepcionSocket("SwitchFibra: Fallo al crear socket TCP");
	}
	
	try {
		sockaddr_in servidor_addr{};
		servidor_addr.sin_family = AF_INET;
		servidor_addr.sin_port = htons(8080);
		inet_pton(AF_INET, "127.0.0.1", &servidor_addr.sin_addr);
		
		if (connect(clienteTCP, (struct sockaddr*)&servidor_addr, sizeof(servidor_addr)) < 0) {
			throw ExcepcionSocket("SwitchFibra: El servidor TCP no responde o esta inactivo");
		}
		
		std::string mensaje = "TRAMA_TCP|" + getId() + "|PUERTOS:" + std::to_string(puertosActivos) + "\n";
		
		int totalEnviado = 0;
		int tamanoMensaje = mensaje.length();
		while (totalEnviado < tamanoMensaje) {
			int enviados = send(clienteTCP, mensaje.c_str() + totalEnviado, tamanoMensaje - totalEnviado, 0);
			if (enviados <= 0) {
				throw ExcepcionSocket("SwitchFibra: Error en send()");
			}
			totalEnviado += enviados;
		}
		
		{
			std::lock_guard<std::mutex> lock(mtx_consola);
			std::cout << "[SwitchFibra " << getId() << "] Trama TCP enviada (" << totalEnviado << " bytes).\n";
		}
		
		char buffer[128];
		int bytesRecibidos = recv(clienteTCP, buffer, sizeof(buffer) - 1, 0);
		if (bytesRecibidos > 0) {
			buffer[bytesRecibidos] = '\0';
			std::lock_guard<std::mutex> lock(mtx_consola);
			std::cout << "[SwitchFibra " << getId() << "] Servidor respondio: " << buffer << "\n";
		} else if (bytesRecibidos == 0) {
			std::lock_guard<std::mutex> lock(mtx_consola);
			std::cout << "[SwitchFibra " << getId() << "] El servidor cerro la conexion.\n";
		}
		
	} catch (...) {
#ifdef _WIN32
		closesocket(clienteTCP);
#else
		close(clienteTCP);
#endif
		throw;
	}
	
#ifdef _WIN32
	closesocket(clienteTCP);
#else
	close(clienteTCP);
#endif
}
