cmake_minimum_required( VERSION 3.3 )

set( CMAKE_VERBOSE_MAKEFILE "ON" )

#project name
project( RemoteControlServer )

get_filename_component( SRC_ROOT ${PROJECT_SOURCE_DIR} ABSOLUTE )

get_filename_component( INC_ROOT ${PROJECT_SOURCE_DIR} ABSOLUTE )

set( REMOTECONTROLSERVER_SRCS
	${SRC_ROOT}/server.c
	${SRC_ROOT}/controlStation.c	
)

set( REMOTECONTROLSERVER_HEADERS
	${INC_ROOT}/protocol.h
	${INC_ROOT}/server.h
)

set( INCLUDE_DIRS
	${INC_ROOT}
	${SRC_ROOT}
)

include_directories( ${INCLUDE_DIRS} )

add_executable( ${PROJECT_NAME} ${REMOTECONTROLSERVER_SRCS} ${REMOTECONTROLSERVER_HEADERS} )
