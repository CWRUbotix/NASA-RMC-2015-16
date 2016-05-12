CC = g++
CFLAGS = -c -Wall
INC_ROBOS = MessageSystem/cpp/Async/include MessageSystem/cpp/Robos/include MessageSystem/cpp/Utilities
INC_ROBOS_PARAMS = $(foreach d, $(INC_ROBOS), -I$d)
INC_GLENN_PARAMS = -Icpp/include

SRC_ROBOS_ASYNC = $(wildcard MessageSystem/cpp/Async/src/Async/*.cpp) MessageSystem/cpp/Async/src/Async/Factories/EngineFactory.cpp
async:
	 $(CC) $(CFLAGS) $(INC_ROBOS) 
