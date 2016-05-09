################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Communications/src/CommReceiver.cpp \
../src/Communications/src/CommTransmitter.cpp 

C_SRCS += \
../src/Communications/src/client.c \
../src/Communications/src/controlStation.c \
../src/Communications/src/server.c 

OBJS += \
./src/Communications/src/CommReceiver.o \
./src/Communications/src/CommTransmitter.o \
./src/Communications/src/client.o \
./src/Communications/src/controlStation.o \
./src/Communications/src/server.o 

C_DEPS += \
./src/Communications/src/client.d \
./src/Communications/src/controlStation.d \
./src/Communications/src/server.d 

CPP_DEPS += \
./src/Communications/src/CommReceiver.d \
./src/Communications/src/CommTransmitter.d 


# Each subdirectory must supply rules for building sources it contributes
src/Communications/src/%.o: ../src/Communications/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Communications/src/%.o: ../src/Communications/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


