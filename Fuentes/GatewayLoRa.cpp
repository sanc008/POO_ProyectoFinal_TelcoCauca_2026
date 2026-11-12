#include "GatewayLoRa.h"
#include "TramaTelemetria.h"
#include "ExcepcionSocket.h"
#include <iostream>
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

GatewayLoRa::GatewayLoRa(std::string _id, float _freq)
	: DispositivoComunicacion(_id, "Gateway LoRa"), frecuenciaMHz(_freq) {
}

void GatewayLoRa::transmitir() {
	SocketNativo clienteUDP = socket(AF_INET, SOCK_DGRAM, 0);
	if (clienteUDP == SOCKET_INVALIDO) {
		throw ExcepcionSocket("GatewayLoRa: Fallo al crear socket UDP");
	}
	
	sockaddr_in dest_addr{};
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(8081);
	inet_pton(AF_INET, "127.0.0.1", &dest_addr.sin_addr);
	
	TramaTelemetria paquete;
	paquete.idEstacion = 101;
	std::strncpy(paquete.tipoDispositivo, "GatewayLoRa", sizeof(paquete.tipoDispositivo) - 1);
	paquete.tipoDispositivo[sizeof(paquete.tipoDispositivo) - 1] = '\0';
	paquete.temperatura = 24.5f;
	paquete.humedad = 60.0f;
	paquete.timestamp = 1700000000;
	
	int bytesEnviados = sendto(clienteUDP, reinterpret_cast<const char*>(&paquete),
							   sizeof(paquete), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
	
	if (bytesEnviados < 0) {
#ifdef _WIN32
		closesocket(clienteUDP);
#else
		close(clienteUDP);
#endif
		throw ExcepcionSocket("GatewayLoRa: Fallo al enviar datagrama UDP");
	}
	
	{
		std::lock_guard<std::mutex> lock(mtx_consola);
		std::cout << "[GatewayLoRa " << getId() << " | " << frecuenciaMHz << " MHz] Datagrama UDP transmitido ("
			<< bytesEnviados << " bytes).\n";
	}
	
#ifdef _WIN32
	closesocket(clienteUDP);
#else
	close(clienteUDP);
#endif
}
