#include "RouterWiFi.h"

RouterWiFi::RouterWiFi(std::string _id, int _canales):DispositivoComunicacion(_id, "Router WiFi 6"), canalesActivos(_canales) {}


void RouterWiFi::transmitir(){
	std::cout<<"\n\n[RouterWiFi "<<idDispositivoComunicacion<<" ]"<<"Conexion exitosa";
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
}
