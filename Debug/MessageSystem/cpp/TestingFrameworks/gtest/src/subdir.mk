################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-all.cc \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-death-test.cc \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-filepath.cc \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-port.cc \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-printers.cc \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-test-part.cc \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-typed-test.cc \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest.cc \
../MessageSystem/cpp/TestingFrameworks/gtest/src/gtest_main.cc 

OBJS += \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-all.o \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-death-test.o \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-filepath.o \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-port.o \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-printers.o \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-test-part.o \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-typed-test.o \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest.o \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest_main.o 

CC_DEPS += \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-all.d \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-death-test.d \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-filepath.d \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-port.d \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-printers.d \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-test-part.d \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest-typed-test.d \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest.d \
./MessageSystem/cpp/TestingFrameworks/gtest/src/gtest_main.d 


# Each subdirectory must supply rules for building sources it contributes
MessageSystem/cpp/TestingFrameworks/gtest/src/%.o: ../MessageSystem/cpp/TestingFrameworks/gtest/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


