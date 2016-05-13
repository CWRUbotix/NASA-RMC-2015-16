#include "ADC/ADC.hpp"

#include "I2C/I2C.hpp"

#define IO_VOLTAGE (3.3)

namespace Sensors {

int ADC::query(float* value, int index) {
        int retval;
	
	I2C::I2C deviceBus(0);
    retval = deviceBus.open();
	if (retval < 0) {return -1;}
    char address = 0x48 + (index / 8);
	retval = deviceBus.setAddress(0x48);
    if (retval < 0) {return -1;}
        
	char cmd[] = {(char)(0b10001100 | ((index << 4) & 0b01110000))}; // 1 pin mode bit, 3 channel select bits, 2 power mode bits, 2 unused
        char buff[2];
        
	retval = deviceBus.sendPacket(cmd, 1);
	if (retval < 0) {return -1;}
	retval = deviceBus.receivePacket(buff, 2);
	if (retval < 0) {return -1;}

	*value = (buff[0]*256 + buff[1]) * (IO_VOLTAGE / (4096.0));
	
	retval = deviceBus.close();
	if (retval < 0) {return -1;}
	return 0;
}

}