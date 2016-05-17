################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include cpp/src/USBSerial/subdir.mk
-include cpp/src/Network/subdir.mk
-include cpp/src/MotorControl/subdir.mk
-include cpp/src/Messages/subdir.mk
-include cpp/src/Localization/subdir.mk
-include cpp/src/I2C/subdir.mk
-include cpp/src/Glenn/subdir.mk
-include cpp/src/CommonUtil/subdir.mk
-include cpp/src/Autonomous/subdir.mk
-include cpp/src/ADC/subdir.mk
-include cpp/subdir.mk
-include RemoteControl/src/subdir.mk
-include MessageSystem/cpp/Utilities_FT/src/subdir.mk
-include MessageSystem/cpp/Utilities/src/Utilities/unitTest/subdir.mk
-include MessageSystem/cpp/Utilities/src/Utilities/subdir.mk
-include MessageSystem/cpp/TutorialRobot/src/GPS/Project_Code/subdir.mk
-include MessageSystem/cpp/TutorialRobot/src/GPS/Nodes/subdir.mk
-include MessageSystem/cpp/TutorialRobot/src/GPS/Messages/subdir.mk
-include MessageSystem/cpp/TestingFrameworks/gtest/src/unittest/subdir.mk
-include MessageSystem/cpp/TestingFrameworks/gtest/src/subdir.mk
-include MessageSystem/cpp/Robos_FT/Robos_FT_Python_Client/src/Nodes/subdir.mk
-include MessageSystem/cpp/Robos_FT/Robos_FT_Python_Client/src/Messages/subdir.mk
-include MessageSystem/cpp/Robos_FT/Robos_FT_Python_Client/src/subdir.mk
-include MessageSystem/cpp/Robos_FT/Robos_FT_Cpp_Client/src/Nodes/subdir.mk
-include MessageSystem/cpp/Robos_FT/Robos_FT_Cpp_Client/src/Messages/subdir.mk
-include MessageSystem/cpp/Robos_FT/Robos_FT_Cpp_Client/src/subdir.mk
-include MessageSystem/cpp/Robos/src/Robos/unitTest/subdir.mk
-include MessageSystem/cpp/Robos/src/Robos/subdir.mk
-include MessageSystem/cpp/Logging/src/Logging/unitTest/subdir.mk
-include MessageSystem/cpp/Logging/src/Logging/subdir.mk
-include MessageSystem/cpp/Async_FT/src/subdir.mk
-include MessageSystem/cpp/Async/src/Async/unitTest/subdir.mk
-include MessageSystem/cpp/Async/src/Async/Factories/subdir.mk
-include MessageSystem/cpp/Async/src/Async/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: NASA_RMC_2015_16

# Tool invocations
NASA_RMC_2015_16: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "NASA_RMC_2015_16" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) NASA_RMC_2015_16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
