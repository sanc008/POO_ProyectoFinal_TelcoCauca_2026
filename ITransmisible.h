#ifndef ITRANSMISIBLE_H
#define ITRANSMISIBLE_H

class ITransmisible {
public:
	virtual~ITransmisible()=default;
	virtual void transmitir() = 0; 
};

#endif

