#ifndef TRAMATELEMETRIA_H
#define TRAMATELEMETRIA_H

#include <cstdint>

// Seg˙n Unidad 9.2: AlineaciÛn estricta a 1 byte (sin padding)
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
