#include "USBSerial.hpp"

namespace USBSerial {
Port::Port(std::string s) {
	SerialStream dev();
	file = -1;
	device = s;
}
Port::~Port() {
	dev.Close();
}
int Port::open() {
	dev.Open(device);
	dev.SetBaudRate(SerialStreamBuf::BAUD_9600);
	dev.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
	dev.SetNumOfStopBits(1);
	dev.SetParity(SerialStreamBuf::PARITY_NONE);
	return 0;
}
int Port::close() {
	dev.Close();
	return 0;
}
int Port::write(char val) {
	dev << val;
	return 0;
}
int Port::write(char * buffer, int len) {
	dev.write(buffer, len);
	return 0;
}
int Port::read(char * buffer, int len) {
	dev.read(buffer, len);
	return len;
}
}
