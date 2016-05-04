#ifndef ADC_HPP_
#define ADC_HPP_

#include "I2C.hpp"

namespace Auton {

/** The ADC class provides access to the robot's ADC boards. */
class ADC {

	/** Get the voltage on the given ADC channel. Must be checked for
	 *  failure.
	 *  @param value the pointer to which the returned voltage is written
	 *  @param index the ADC channel to use 
	 *  @return 0 on success, or a negative value on failure
	 */
	int query(float *value, int index);

};

}

#endif // ADC_HPP_
