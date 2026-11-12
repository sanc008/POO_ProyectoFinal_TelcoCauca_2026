#ifndef TRAMATELEMETRIA_H
#define TRAMATELEMETRIA_H

#include <cstdint>


#pragma pack(push, 1)
struct TramaTelemetria {
	std::uint32_t idEstacion;      
	char tipoDispositivo[16];      
	float temperatura;             
	float humedad;                 
	std::uint64_t timestamp;       
};
#pragma pack(pop) 

#endif
