################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/CommonMemory.cpp \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/PythonBridge_unit.cpp \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/Semaphore_unit.cpp \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/Signaler.cpp \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/SimpleSemaphoreTest.cpp \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/Waiter.cpp \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/catchConfig.cpp 

CC_SRCS += \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/BoundTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/BulkLoadTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/DumpRestoreTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/InstantiationTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/IteratorTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/LargeTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/RelationTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/SimpleTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/StructureTest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/speedtest-tune.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/speedtest.cc \
../MessageSystem/cpp/Utilities/src/Utilities/unitTest/tpunit.cc 

OBJS += \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/BoundTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/BulkLoadTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/CommonMemory.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/DumpRestoreTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/InstantiationTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/IteratorTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/LargeTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/PythonBridge_unit.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/RelationTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/Semaphore_unit.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/Signaler.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/SimpleSemaphoreTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/SimpleTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/StructureTest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/Waiter.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/catchConfig.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/speedtest-tune.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/speedtest.o \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/tpunit.o 

CC_DEPS += \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/BoundTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/BulkLoadTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/DumpRestoreTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/InstantiationTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/IteratorTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/LargeTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/RelationTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/SimpleTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/StructureTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/speedtest-tune.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/speedtest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/tpunit.d 

CPP_DEPS += \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/CommonMemory.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/PythonBridge_unit.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/Semaphore_unit.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/Signaler.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/SimpleSemaphoreTest.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/Waiter.d \
./MessageSystem/cpp/Utilities/src/Utilities/unitTest/catchConfig.d 


# Each subdirectory must supply rules for building sources it contributes
MessageSystem/cpp/Utilities/src/Utilities/unitTest/%.o: ../MessageSystem/cpp/Utilities/src/Utilities/unitTest/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

MessageSystem/cpp/Utilities/src/Utilities/unitTest/%.o: ../MessageSystem/cpp/Utilities/src/Utilities/unitTest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


