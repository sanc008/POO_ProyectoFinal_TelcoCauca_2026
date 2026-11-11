#ifndef EXCEPCIONNODORED_H
#define EXCEPCIONNODORED_H
#include <stdexcept>
#include <string>
class ExcepcionNodoRed:public std::runtime_error{
public:
	ExcepcionNodoRed(const std::string& errorPropio);
	~ExcepcionNodoRed();
private:
};

#endif

