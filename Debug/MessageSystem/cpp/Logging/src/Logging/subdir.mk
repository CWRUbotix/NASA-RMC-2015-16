################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MessageSystem/cpp/Logging/src/Logging/Factory.cpp \
../MessageSystem/cpp/Logging/src/Logging/Logger.cpp \
../MessageSystem/cpp/Logging/src/Logging/LoggingLevels.cpp 

OBJS += \
./MessageSystem/cpp/Logging/src/Logging/Factory.o \
./MessageSystem/cpp/Logging/src/Logging/Logger.o \
./MessageSystem/cpp/Logging/src/Logging/LoggingLevels.o 

CPP_DEPS += \
./MessageSystem/cpp/Logging/src/Logging/Factory.d \
./MessageSystem/cpp/Logging/src/Logging/Logger.d \
./MessageSystem/cpp/Logging/src/Logging/LoggingLevels.d 


# Each subdirectory must supply rules for building sources it contributes
MessageSystem/cpp/Logging/src/Logging/%.o: ../MessageSystem/cpp/Logging/src/Logging/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


