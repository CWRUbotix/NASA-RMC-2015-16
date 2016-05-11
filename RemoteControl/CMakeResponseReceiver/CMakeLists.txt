cmake_minimum_required( VERSION 3.3 )

set( CMAKE_VERBOSE_MAKEFILE "ON" )

#project name
project( ResponseReceiver )

get_filename_component( SRC_ROOT ${PROJECT_SOURCE_DIR}/../src ABSOLUTE )

get_filename_component( INC_ROOT ${PROJECT_SOURCE_DIR}/../include ABSOLUTE )

set( RESPONSERECEIEVER_SRCS
	${SRC_ROOT}/client.cpp
	${SRC_ROOT}/responseReceiver.cpp
)

set( RESPONSERECEIEVER_HEADERS
	${INC_ROOT}/client.hpp
	${INC_ROOT}/protocol.hpp
	${INC_ROOT}/commandReceiver.hpp
)

set( INCLUDE_DIRS
	${INC_ROOT}
	${SRC_ROOT}
)

include_directories( ${INCLUDE_DIRS} )

add_executable( ${PROJECT_NAME} ${RESPONSERECEIEVER_SRCS} ${RESPONSERECEIEVER_HEADERS} )
