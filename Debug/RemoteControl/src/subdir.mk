################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RemoteControl/src/MotorUtil.cpp \
../RemoteControl/src/client.cpp \
../RemoteControl/src/commandReceiver.cpp \
../RemoteControl/src/controlStation.cpp \
../RemoteControl/src/responseReceiver.cpp \
../RemoteControl/src/server.cpp 

OBJS += \
./RemoteControl/src/MotorUtil.o \
./RemoteControl/src/client.o \
./RemoteControl/src/commandReceiver.o \
./RemoteControl/src/controlStation.o \
./RemoteControl/src/responseReceiver.o \
./RemoteControl/src/server.o 

CPP_DEPS += \
./RemoteControl/src/MotorUtil.d \
./RemoteControl/src/client.d \
./RemoteControl/src/commandReceiver.d \
./RemoteControl/src/controlStation.d \
./RemoteControl/src/responseReceiver.d \
./RemoteControl/src/server.d 


# Each subdirectory must supply rules for building sources it contributes
RemoteControl/src/%.o: ../RemoteControl/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Utilities/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


