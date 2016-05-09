################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RemoteControlServer/CMakeFiles/feature_tests.c 

CXX_SRCS += \
../RemoteControlServer/CMakeFiles/feature_tests.cxx 

OBJS += \
./RemoteControlServer/CMakeFiles/feature_tests.o 

C_DEPS += \
./RemoteControlServer/CMakeFiles/feature_tests.d 

CXX_DEPS += \
./RemoteControlServer/CMakeFiles/feature_tests.d 


# Each subdirectory must supply rules for building sources it contributes
RemoteControlServer/CMakeFiles/%.o: ../RemoteControlServer/CMakeFiles/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RemoteControlServer/CMakeFiles/%.o: ../RemoteControlServer/CMakeFiles/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DGXX_EXPERIMENTAL_CXX0X -D__cplusplus=201103L -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/src/MotorControl/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/src/Localization/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/src/I2C/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/src/Communications/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/src/Autonomous/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Robos/include" -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/MessageSystem/cpp/Async/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


