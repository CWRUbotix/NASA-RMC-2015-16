################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MessageSystem/cpp/Async/src/Async/unitTest/AsyncExecution_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/Async_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/ContinuableWorkItem_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/Engine_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/MockScheduler.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/MockWorkItem.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/Promise_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/SimpleContinuation_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/TestUtilities.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/ValueHolder_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/WorkItemAndScheduler_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/WorkItemStateMachineUnitTestInterface.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/WorkItemStateMachine_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/WorkItem_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/WorkerThread_unit.cpp \
../MessageSystem/cpp/Async/src/Async/unitTest/catchConfig.cpp 

OBJS += \
./MessageSystem/cpp/Async/src/Async/unitTest/AsyncExecution_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/Async_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/ContinuableWorkItem_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/Engine_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/MockScheduler.o \
./MessageSystem/cpp/Async/src/Async/unitTest/MockWorkItem.o \
./MessageSystem/cpp/Async/src/Async/unitTest/Promise_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/SimpleContinuation_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/TestUtilities.o \
./MessageSystem/cpp/Async/src/Async/unitTest/ValueHolder_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkItemAndScheduler_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkItemStateMachineUnitTestInterface.o \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkItemStateMachine_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkItem_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkerThread_unit.o \
./MessageSystem/cpp/Async/src/Async/unitTest/catchConfig.o 

CPP_DEPS += \
./MessageSystem/cpp/Async/src/Async/unitTest/AsyncExecution_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/Async_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/ContinuableWorkItem_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/Engine_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/MockScheduler.d \
./MessageSystem/cpp/Async/src/Async/unitTest/MockWorkItem.d \
./MessageSystem/cpp/Async/src/Async/unitTest/Promise_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/SimpleContinuation_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/TestUtilities.d \
./MessageSystem/cpp/Async/src/Async/unitTest/ValueHolder_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkItemAndScheduler_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkItemStateMachineUnitTestInterface.d \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkItemStateMachine_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkItem_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/WorkerThread_unit.d \
./MessageSystem/cpp/Async/src/Async/unitTest/catchConfig.d 


# Each subdirectory must supply rules for building sources it contributes
MessageSystem/cpp/Async/src/Async/unitTest/%.o: ../MessageSystem/cpp/Async/src/Async/unitTest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


