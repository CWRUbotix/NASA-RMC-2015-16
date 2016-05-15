################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MessageSystem/cpp/Robos/src/Robos/unitTest/CountTestNode.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/MasterNode_unit.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/MessageBase_unit.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/NodeDatabase_unit.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/Robos_unit.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/ShutdownTestNode.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestCountInitNode.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestCountMessage.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestInitNode.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageA.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageB.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageC.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestNode.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestNodeNameTemplate.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/TestNodeSubscriberTemplate.cpp \
../MessageSystem/cpp/Robos/src/Robos/unitTest/catchConfig.cpp 

OBJS += \
./MessageSystem/cpp/Robos/src/Robos/unitTest/CountTestNode.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/MasterNode_unit.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/MessageBase_unit.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/NodeDatabase_unit.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/Robos_unit.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/ShutdownTestNode.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestCountInitNode.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestCountMessage.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestInitNode.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageA.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageB.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageC.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestNode.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestNodeNameTemplate.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestNodeSubscriberTemplate.o \
./MessageSystem/cpp/Robos/src/Robos/unitTest/catchConfig.o 

CPP_DEPS += \
./MessageSystem/cpp/Robos/src/Robos/unitTest/CountTestNode.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/MasterNode_unit.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/MessageBase_unit.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/NodeDatabase_unit.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/Robos_unit.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/ShutdownTestNode.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestCountInitNode.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestCountMessage.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestInitNode.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageA.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageB.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestMessageC.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestNode.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestNodeNameTemplate.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/TestNodeSubscriberTemplate.d \
./MessageSystem/cpp/Robos/src/Robos/unitTest/catchConfig.d 


# Each subdirectory must supply rules for building sources it contributes
MessageSystem/cpp/Robos/src/Robos/unitTest/%.o: ../MessageSystem/cpp/Robos/src/Robos/unitTest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Utilities/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


