cmake_minimum_required( VERSION 3.3 )

set( CMAKE_VERBOSE_MAKEFILE "ON" )

#project name
project( ControlStaion )

get_filename_component( SRC_ROOT ${PROJECT_SOURCE_DIR}/../src ABSOLUTE )

get_filename_component( INC_ROOT ${PROJECT_SOURCE_DIR}/../include ABSOLUTE )

set( GCC_COMPILE_FLAGS
	"--std=c++11"
)

set( CONTROLSTATION_SRCS
	${SRC_ROOT}/MotorUtil.cpp
	${SRC_ROOT}/server.cpp
	${SRC_ROOT}/commandReceiver.cpp
	${SRC_ROOT}/controlStation.cpp
)

set( CONTROLSTATION_HEADERS
	${INC_ROOT}/MotorUtil.hpp
	${INC_ROOT}/protocol.hpp
	${INC_ROOT}/server.hpp
	${INC_ROOT}/commandProtocol.hpp
	${INC_ROOT}/commandReceiver.hpp
)

set( INCLUDE_DIRS
	${INC_ROOT}
	${SRC_ROOT}
)

include_directories( ${INCLUDE_DIRS} )

add_definitions( ${GCC_COMPILE_FLAGS} )

add_executable( ${PROJECT_NAME} ${CONTROLSTATION_SRCS} ${CONTROLSTATION_HEADERS} )
