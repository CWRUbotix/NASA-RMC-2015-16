################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MotorControl/src/MotorControl.cpp \
../src/MotorControl/src/MotorControlNode.cpp \
../src/MotorControl/src/MotorUtil.cpp 

OBJS += \
./src/MotorControl/src/MotorControl.o \
./src/MotorControl/src/MotorControlNode.o \
./src/MotorControl/src/MotorUtil.o 

CPP_DEPS += \
./src/MotorControl/src/MotorControl.d \
./src/MotorControl/src/MotorControlNode.d \
./src/MotorControl/src/MotorUtil.d 


# Each subdirectory must supply rules for building sources it contributes
src/MotorControl/src/%.o: ../src/MotorControl/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


