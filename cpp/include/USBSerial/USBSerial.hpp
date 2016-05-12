#include <SerialStream.h>
#include <string>

#ifndef USBSERIAL_HPP_
#define USBSERIAL_HPP_

using namespace LibSerial;

namespace USBSerial {
class Port {
public:
	SerialStream dev;
	int file;
	std::string device;
public:
	int open();
	int close();
	int write(char val);
	int write(char * buffer, int len);
	int read(char* buffer, int len);
	Port(std::string s);
	~Port();
};
}
#endif
