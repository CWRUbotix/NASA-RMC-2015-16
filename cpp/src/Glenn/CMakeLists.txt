# tell CMake to yell if using version less than 3.3
cmake_minimum_required( VERSION 3.3 )

# NEED to tell CMake where our custom CMake files our (*.cmake files). There are 2 directories.
# find paths to the directories.
get_filename_component( ROBOS_CMAKE_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../../../MessagingSystem/cmake ABSOLUTE )
get_filename_component( CUSTOM_CMAKE_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake ABSOLUTE )

# source code root directory
get_filename_component( SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE )

# Public header file root directory
get_filename_component( INC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include ABSOLUTE )

# tell CMake about them. This list is kind of like CMake's internal version of the $PATH env variable.
list( APPEND CMAKE_MODULE_PATH ${CUSTOM_CMAKE_MODULES}/modules ${ROBOS_CMAKE_MODULES}/modules )

# declare a project named "Glenn" to be a C++ project
Project( GlennUnitTests CXX )


set( ${PROJECT_NAME}_SRCS
    # PROJECT CODE (Non Nodes)
    ${SRC_ROOT}/USBSerial/USBSerial.cpp

    ${SRC_ROOT}/Network/client.cpp
    ${SRC_ROOT}/Network/server.cpp

    ${SRC_ROOT}/CommonUtil/MotorUtil.cpp

    ${SRC_ROOT}/MotorControl/MotorControl.cpp
    
    # Robos Interfacing (Nodes and Messages)
    ${SRC_ROOT}/Messages/MessagesGeneral.cpp
    ${SRC_ROOT}/Messages/MessagesComm.cpp

    ${SRC_ROOT}/Network/CommReceiver.cpp
    ${SRC_ROOT}/Network/CommTransmitter.cpp

    ${SRC_ROOT}/MotorControl/MotorControlNode.cpp

    ${SRC_ROOT}/Glenn/main.cpp
)

set( ${PROJECT_NAME}_PUBLIC_HEADERS
    # PROJECT CODE (Non Nodes and Messages)
    ${INC_ROOT}/USBSerial/USBSerial.hpp

    ${INC_ROOT}/Network/client.hpp
    ${INC_ROOT}/Network/Network.hpp
    ${INC_ROOT}/Network/protocol.hpp
    ${INC_ROOT}/Network/server.hpp

    ${INC_ROOT}/CommonUtil/MotorUtil.hpp

    ${INC_ROOT}/MotorControl/MotorControl.hpp

    # Robos interfacing code (Nodes and Messages)
    ${INC_ROOT}/Messages/MessagesComm.hpp
    ${INC_ROOT}/Messages/MessagesGeneral.hpp
    ${INC_ROOT}/Messages/MessagesMotorControl.hpp

    ${INC_ROOT}/Network/CommReceiver.hpp
    ${INC_ROOT}/Network/CommTransmitter.hpp

    ${INC_ROOT}/MotorControl/MotorControlNode.hpp
)

set( ${PROJECT_NAME}_PRIVATE_HEADERS
    
)

set( INCLUDE_DIRS
    ${INC_ROOT}
    ${SRC_ROOT}
    ${CONFIG_ROOT}
)

# Need to include necessary system libraries and GNUInstallDirs
# (which sets CMake variables for installation). Note these are platform dependent.
if( MSVC )
    include( GNUInstallDirs )
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include( GNUInstallDirs )
    set(TARGET_PTHREADS_LIB "pthread")
    set(TARGET_UUID_LIB "uuid")
    set(TARGET_SERIAL_LIB "serial")
elseif( APPLE )
    include( GNUInstallDirs )
    set(TARGET_PTHREADS_LIB "pthread")
    set(TARGET_UUID_LIB "uuid")
    set(TARGET_SERIAL_LIB "serial")
else()
    message(SEND_ERROR "OS [${CMAKE_SYSTEM_NAME}] not supported")
endif()

# link this project with all libraries we need
set( ${PROJECT_NAME}_IMPORTED_LIST
    # all libraries to import when building Robos
    "Logging"
    "Utilities"
    "Async"
    "Robos"
    "I2C"
    "ADC"
)

# Actually link everything. This is a provided CMake module to link everything together.
include(ProjectLinker)

# All imported libraries have their own headers we need to include to use them. ProjectLinker gives us
# them as a variable, so add them to the list of directories we will look for files in.
list( APPEND INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDES} )
include_directories( ${INCLUDE_DIRS} )

# create an executable
add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_PUBLIC_HEADERS} ${${PROJECT_NAME}_PRIVATE_HEADERS} )

# link the executable together
if( ${${PROJECT_NAME}_IMPORTED_LIBS_LENGTH} GREATER 0 )
    target_link_libraries( ${PROJECT_NAME}
    ${TARGET_PTHREADS_LIB}
    ${TARGET_SERIAL_LIB}
    ${${PROJECT_NAME}_IMPORTED_LIBS} )
endif()

# install our executable. This tells CMake WHERE to put everything when it builds.
install( TARGETS ${PROJECT_NAME}
         RUNTIME        DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# if using Visual Studio we want to include the .pdb files in our distribution.
if( MSVC )
    get_filename_component( PDB_DIR ${OUT_ROOT}/stuff/${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ABSOLUTE )
    install( FILES ${PDB_DIR}/${PROJECT_NAME}.pdb
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
