# this is the required version of CMake necessary
# to run. CMake will fail if you have anything
# less than 3.3
cmake_minimum_required( VERSION 3.3 )

# when CMake generates Makefiles, this setting
# will allow them to print to the console.
set( CMAKE_VERBOSE_MAKEFILE "ON" )

# this points to the root of the cmake directory
# which contains all the toolchains and modules
# (/../ is the shorthand for moving UP a directory. So "stuff/foo/../" will resolve to the "stuff/" directory.)
# This should point to <MessagingSystem_Top_Level_Directory>/cmake. You can use usefule things like:
# ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cmake if the location of your CMakeLists.txt file is 4 subdirectories under
# <MessagingSystem_Top_Level_Directory>
#
get_filename_component( CMAKE_LOCAL_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../MessagingSystem/cmake ABSOLUTE )

# let CMake use files in the <MessagingSystem_Top_Level_Directory>/cmake/modules directory
list( APPEND CMAKE_MODULE_PATH ${CMAKE_LOCAL_ROOT}/modules )

# Project name
project( I2C CXX )

# source code root directory
get_filename_component( SRC_ROOT ${PROJECT_SOURCE_DIR} ABSOLUTE )

# Public header file root directory
get_filename_component( INC_ROOT ${PROJECT_SOURCE_DIR}/../include ABSOLUTE )

get_filename_component( MESSAGE_ROOT ${PROJECT_SOURCE_DIR}/../../Messages ABSOLUTE )

get_filename_component( COMMONDATASTRUCTURES_ROOT ${PROJECT_SOURCE_DIR}/../../CommonDataStructures ABSOLUTE )

get_filename_component( CONFIG_ROOT ${PROJECT_SOURCE_DIR}/../../../MessagingSystem/build/out/include ABSOLUTE )

# this is where we could get the Version numbering from Version.h and
# save them as CMake variables. for now, lets just declare them
set( PROJECT_VERSION_MAJOR "1" )
set( PROJECT_VERSION_MINOR "0" )
set( PROJECT_VERSION_PATCH "0" )

# Source files
set( I2C_SRCS
    # Config (provided by the build system. This file includes paths to logFile directory)
    # ${CONFIG_ROOT}/NetworkingConfig.cpp

    # put your .cpp files here.
    ${SRC_ROOT}/I2C.cpp
)

# Public header files (installed together with libraries)
set( I2C_PUBLIC_HEADERS
    # put your .hpp files here that you want clients of your code to be able to #include.
    ${INC_ROOT}/LibraryExport.hpp
    ${INC_ROOT}/I2C.hpp
)

set( I2C_PRIVATE_HEADERS
    # logging
    # ${CONFIG_ROOT}/NetworkingConfig.hpp

    # put your .hpp files here that you don't want clients to have access to.
)

# group together all public headers. 
source_group( PublicHeaders FILES ${I2C_PUBLIC_HEADERS} )

# This tells CMake where to look for files. These determine how you #include things in your files.
set( INCLUDE_DIRS
    ${INC_ROOT}
    ${SRC_ROOT}
    ${CONFIG_ROOT}
    ${MESSAGE_ROOT}/include
    ${COMMONDATASTRUCTURES_ROOT}/include
)

# set target specific compiler definitions
# this should ONLY be definitions needed to build the source code.
# examples: macros ON/OFF, etc. Don't worry about this.
set( I2C_COMPILE_DEFINITIONS )

# check required libraries and header files and such.
# this will fail CMake if set to False due to required
# modules requiring their own dependencies.
#
# In other words, this will fail your build if CMake cannot find everything it needs.
set( DEPENDENCY_CHECK FALSE )

# DO NOT CHANGE.
# This is a built in CMake module that defines useful paths like where to install everything. Don't worry about it
# but don't get rid of it.
include( GNUInstallDirs )


# You need to link your code to Robos. Below are the all the libraries you need to link to to use Robos.
# You can add any libraries you need after these.
set( ${PROJECT_NAME}_IMPORTED_LIST
    # all libraries to import when building Robos
    "Logging"
    "Utilities"
    "Async"
    "Robos"
)

# Actually link everything. This is a provided CMake module to link everything together.
include(ProjectLinker)


# All imported libraries have their own headers we need to include to use them. ProjectLinker gives us
# them as a variable, so add them to the list of directories we will look for files in.
list( APPEND INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDES} )


# If CMake couldn't find everything it needed, then fail the build.
if( NOT DEPENDENCY_CHECK )
    message( SEND_ERROR "Required header files or libraries not found" )
endif()

# Actually tell CMake these are the directories we want to look for files in.
include_directories( ${INCLUDE_DIRS} )

# this is kind of redundant, but in case you wanted to build multiple projects in this CMakeLists.txt
set( I2C_LIB_NAME ${PROJECT_NAME} )


# Shared Library export header file support. DO NOT CHANGE
include( GenerateExportHeader )

# actually tell CMake to build a shared library. This will create a shared library with the name: ${<PROJECT_NAME>_LIB_NAME}
# and will use: ${<PROJECT_NAME>_SRCS} ${<PROJECT_NAME>_PUBLIC_HEADERS} ${<PROJECT_NAME>_PRIVATE_HEADERS} to build the library.
add_library( ${I2C_LIB_NAME} SHARED ${I2C_SRCS} ${I2C_PUBLIC_HEADERS} ${I2C_PRIVATE_HEADERS})

# link the library we just created to all the libraries that it needs to run.
if( ${${PROJECT_NAME}_IMPORTED_LIBS_LENGTH} GREATER 0 )
    target_link_libraries( ${I2C_LIB_NAME} ${${PROJECT_NAME}_IMPORTED_LIBS} )
endif()
if( ${${PROJECT_NAME}_STATIC_LIBS_LENGTH} GREATER 0 )
    target_link_libraries( ${I2C_LIB_NAME} ${${PROJECT_NAME}_STATIC_LIBS} )
endif()

# Tell CMake some configuration information about our library
set_target_properties( ${I2C_LIB_NAME} PROPERTIES
    PUBLIC_HEADER       "${I2C_PUBLIC_HEADERS}"
    COMPILE_DEFINITIONS "${I2C_COMPILE_DEFINITIONS}"
    SOVERSION           "${PROJECT_VERSION_MAJOR}"
    VERSION             "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)

# install our library. This tells CMake WHERE to put everything when it builds.
install( TARGETS ${I2C_LIB_NAME}
         RUNTIME        DESTINATION ${CMAKE_INSTALL_BINDIR}
         LIBRARY        DESTINATION ${CMAKE_INSTALL_LIBDIR}
         ARCHIVE        DESTINATION ${CMAKE_INSTALL_LIBDIR}
         PUBLIC_HEADER  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/I2C
)

# if using Visual Studio we want to include the .pdb files in our distribution.
if( MSVC )
    get_filename_component( PDB_DIR ${OUT_ROOT}/stuff/${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ABSOLUTE )
    install( FILES ${PDB_DIR}/${PROJECT_NAME}.pdb
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
