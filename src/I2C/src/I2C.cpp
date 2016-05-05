/*
 * I2C.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: anno
 */
#include "I2C.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cstdio>

namespace I2C {
int I2C::file = -1;

int I2C::open() {
	file = ::open("/dev/i2c-0", O_RDWR);
	if (file < 0) {
		perror("Failed to open the I2C bus");
		return -1;
	}
	return 0;
}

int I2C::close() {
	int retval = ::close(file);
	if (retval < 0) {
		perror("Failed to close the I2C bus");
		return -1;
	}
	file = -1;
	return 0;
}

int I2C::setAddress(char addr) {
	int retval = ioctl(file, I2C_SLAVE_FORCE, addr);
	if (retval < 0) {
		perror("Failed to set the I2C target address");
		return -1;
	}
	return 0;
}

int I2C::sendPacket(const char* buffer, int length) {
	int bytesWritten = write(file, buffer, length);
	if (bytesWritten < 0) {
		perror("Failed to send I2C packet");
		return -1;
	}
	return bytesWritten;
}

int I2C::receivePacket(char* buffer, int length) {
	int bytesRead = read(file, buffer, length);
	if (bytesRead < 0) {
		perror("Failed to recieve I2C packet");
		return -1;
	}
	return bytesRead;
}

}

