################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RemoteControlServer/controlStation.c \
../RemoteControlServer/server.c 

OBJS += \
./RemoteControlServer/controlStation.o \
./RemoteControlServer/server.o 

C_DEPS += \
./RemoteControlServer/controlStation.d \
./RemoteControlServer/server.d 


# Each subdirectory must supply rules for building sources it contributes
RemoteControlServer/%.o: ../RemoteControlServer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/anno/Projects/Eclipse C++ Workspace/NASA_RMC_2015_16/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


