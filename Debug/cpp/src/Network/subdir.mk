################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cpp/src/Network/CommReceiver.cpp \
../cpp/src/Network/CommTransmitter.cpp \
../cpp/src/Network/client.cpp \
../cpp/src/Network/server.cpp \
../cpp/src/Network/testClient.cpp \
../cpp/src/Network/testServer.cpp 

OBJS += \
./cpp/src/Network/CommReceiver.o \
./cpp/src/Network/CommTransmitter.o \
./cpp/src/Network/client.o \
./cpp/src/Network/server.o \
./cpp/src/Network/testClient.o \
./cpp/src/Network/testServer.o 

CPP_DEPS += \
./cpp/src/Network/CommReceiver.d \
./cpp/src/Network/CommTransmitter.d \
./cpp/src/Network/client.d \
./cpp/src/Network/server.d \
./cpp/src/Network/testClient.d \
./cpp/src/Network/testServer.d 


# Each subdirectory must supply rules for building sources it contributes
cpp/src/Network/%.o: ../cpp/src/Network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Utilities/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


