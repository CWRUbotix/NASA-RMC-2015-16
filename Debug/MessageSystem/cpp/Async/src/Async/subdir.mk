################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MessageSystem/cpp/Async/src/Async/ConcurrencyStates.cpp \
../MessageSystem/cpp/Async/src/Async/ContinuableWorkItem.cpp \
../MessageSystem/cpp/Async/src/Async/Engine.cpp \
../MessageSystem/cpp/Async/src/Async/JobPriorities.cpp \
../MessageSystem/cpp/Async/src/Async/PromiseBaseImpl.cpp \
../MessageSystem/cpp/Async/src/Async/Result.cpp \
../MessageSystem/cpp/Async/src/Async/Scheduler.cpp \
../MessageSystem/cpp/Async/src/Async/SettlementStates.cpp \
../MessageSystem/cpp/Async/src/Async/WorkItem.cpp \
../MessageSystem/cpp/Async/src/Async/WorkItemStateMachine.cpp \
../MessageSystem/cpp/Async/src/Async/WorkItemStates.cpp \
../MessageSystem/cpp/Async/src/Async/WorkerThread.cpp 

OBJS += \
./MessageSystem/cpp/Async/src/Async/ConcurrencyStates.o \
./MessageSystem/cpp/Async/src/Async/ContinuableWorkItem.o \
./MessageSystem/cpp/Async/src/Async/Engine.o \
./MessageSystem/cpp/Async/src/Async/JobPriorities.o \
./MessageSystem/cpp/Async/src/Async/PromiseBaseImpl.o \
./MessageSystem/cpp/Async/src/Async/Result.o \
./MessageSystem/cpp/Async/src/Async/Scheduler.o \
./MessageSystem/cpp/Async/src/Async/SettlementStates.o \
./MessageSystem/cpp/Async/src/Async/WorkItem.o \
./MessageSystem/cpp/Async/src/Async/WorkItemStateMachine.o \
./MessageSystem/cpp/Async/src/Async/WorkItemStates.o \
./MessageSystem/cpp/Async/src/Async/WorkerThread.o 

CPP_DEPS += \
./MessageSystem/cpp/Async/src/Async/ConcurrencyStates.d \
./MessageSystem/cpp/Async/src/Async/ContinuableWorkItem.d \
./MessageSystem/cpp/Async/src/Async/Engine.d \
./MessageSystem/cpp/Async/src/Async/JobPriorities.d \
./MessageSystem/cpp/Async/src/Async/PromiseBaseImpl.d \
./MessageSystem/cpp/Async/src/Async/Result.d \
./MessageSystem/cpp/Async/src/Async/Scheduler.d \
./MessageSystem/cpp/Async/src/Async/SettlementStates.d \
./MessageSystem/cpp/Async/src/Async/WorkItem.d \
./MessageSystem/cpp/Async/src/Async/WorkItemStateMachine.d \
./MessageSystem/cpp/Async/src/Async/WorkItemStates.d \
./MessageSystem/cpp/Async/src/Async/WorkerThread.d 


# Each subdirectory must supply rules for building sources it contributes
MessageSystem/cpp/Async/src/Async/%.o: ../MessageSystem/cpp/Async/src/Async/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Utilities/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


