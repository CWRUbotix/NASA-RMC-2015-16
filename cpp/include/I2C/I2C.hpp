#ifndef I2C_HPP_
#define I2C_HPP_

#include "I2C/LibraryExport.hpp"

namespace I2C {


/** The I2C class represents a connection to an I2C bus, where the program
 *  acts as the master and the other devices on the bus are its slaves.
 */
class I2C_API I2C {
private:
	static int file;
public:
	/** Open a connection to the bus. This connections lasts until it is
	 *  closed.
	 *  @return 0 on success, or a negative number on failure
	 */
	static int open();

	/** Close a connection to the bus.
	 *  @return 0 on success, or a negative number on failure
	 */
	static int close();

	/** Set the address of the slave to communicate with.
	 *  Precondition: the connection must be open.
	 *  @param address the slave address, ranging from 0 to 127
	 *  @return 0 on success, or a negative number on failure
	 */
	static int setAddress(char address);

	/** Send a packet to the selected slave.
	 *  Precondition: the connection must be open.
	 *  Precondition: an address must have been selected.
	 *  @param buffer the pointer to the readonly buffer to send
	 *  @param length the length of the buffer, in bytes
	 *  @return On success, the return value is the number of bytes
	 *  written, which may be less than the packet length or may be zero.
	 *  On failure, the return value is negative.
	 */
	static int sendPacket(const char* buffer, int length);

	/** Receive a packet from the selected slave.
	 *  Preconsition: the connection must be open.
	 *  Precondition: an address must have been selected.
	 *  @param buffer the pointer to the buffer that the packet will be
	 *  written to.
	 *  @param length the length of the packet to receive, in bytes
	 *  @return On success, the return value is the number of bytes read,
	 *  which may be less than the number expected or may be zero. On
	 *  On failure, the return value is negative.
	 */
	static int receivePacket(char* buffer, int length);
};
}



#endif
