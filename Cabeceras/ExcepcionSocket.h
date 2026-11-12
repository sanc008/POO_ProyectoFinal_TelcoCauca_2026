#ifndef EXCEPCIONSOCKET_H
#define EXCEPCIONSOCKET_H

#include <stdexcept>
#include <string>

class ExcepcionSocket : public std::runtime_error {
public:
	explicit ExcepcionSocket(const std::string& msg):std::runtime_error("[Error de Red] " + msg) {}
};

#endif
