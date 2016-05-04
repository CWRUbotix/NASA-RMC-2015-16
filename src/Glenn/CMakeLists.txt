# tell CMake to yell if using version less than 3.3
cmake_minimum_required( VERSION 3.3 )

# NEED to tell CMake where our custom CMake files our (*.cmake files). There are 2 directories.
# find paths to the directories.
get_filename_component( ROBOS_CMAKE_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../../MessagingSystem/cmake ABSOLUTE )
get_filename_component( CUSTOM_CMAKE_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../cmake ABSOLUTE )

# tell CMake about them. This list is kind of like CMake's internal version of the $PATH env variable.
list( APPEND CMAKE_MODULE_PATH ${CUSTOM_CMAKE_MODULES}/modules ${ROBOS_CMAKE_MODULES}/modules )

# declare a project named "Glenn" to be a C++ project
Project( Glenn CXX )

if( MSVC )
    include( GNUInstallDirs )
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include( GNUInstallDirs )
    set(TARGET_PTHREADS_LIB "pthread")
    set(TARGET_UUID_LIB "uuid")
elseif( APPLE )
    include( GNUInstallDirs )
    set(TARGET_PTHREADS_LIB "pthread")
    set(TARGET_UUID_LIB "uuid")
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
    "Communications"
)

# Actually link everything. This is a provided CMake module to link everything together.
include(ProjectLinker)

# All imported libraries have their own headers we need to include to use them. ProjectLinker gives us
# them as a variable, so add them to the list of directories we will look for files in.
include_directories( ${${PROJECT_NAME}_INCLUDES} )

# create an executable
add_executable( ${PROJECT_NAME} main.cpp )

# link the executable together
if( ${${PROJECT_NAME}_IMPORTED_LIBS_LENGTH} GREATER 0 )
    target_link_libraries( ${PROJECT_NAME}
    ${TARGET_PTHREADS_LIB}
    ${${PROJECT_NAME}_IMPORTED_LIBS} )
endif()

# install our library. This tells CMake WHERE to put everything when it builds.
install( TARGETS ${PROJECT_NAME}
         RUNTIME        DESTINATION ${CMAKE_INSTALL_BINDIR}
         # LIBRARY        DESTINATION ${CMAKE_INSTALL_LIBDIR}
         # ARCHIVE        DESTINATION ${CMAKE_INSTALL_LIBDIR}
         # PUBLIC_HEADER  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Communications
)

# if using Visual Studio we want to include the .pdb files in our distribution.
if( MSVC )
    get_filename_component( PDB_DIR ${OUT_ROOT}/stuff/${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ABSOLUTE )
    install( FILES ${PDB_DIR}/${PROJECT_NAME}.pdb
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
