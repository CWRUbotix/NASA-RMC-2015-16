# tell CMake to yell if using version less than 3.3
cmake_minimum_required( VERSION 3.3 )

# NEED to tell CMake where our custom CMake files our (*.cmake files). There are 2 directories.
# find paths to the directories.
get_filename_component( ROBOS_CMAKE_MODULES ${PROJECT_DIR}/../../MessagingSystem/cmake ABSOLUTE )
get_filename_component( CUSTOM_CMAKE_MODULES ${PROJECT_DIR}/../cmake ABSOLUTE )

# tell CMake about them. This list is kind of like CMake's internal version of the $PATH env variable.
list( APPEND CMAKE_MODULE_PATH ${CUSTOM_CMAKE_MODULES}/modules ${ROBOS_CMAKE_MODULES}/modules )

# declare a project named "Glenn" to be a C++ project
Project( Glenn CXX )

# link this project with all libraries we need
set( ${PROJECT_NAME}_IMPORTED_LIST
    # all libraries to import when building Robos
    "Logging"
    "Utilities"
    "Async"
    "Robos"
    "Networking"
)

# Actually link everything. This is a provided CMake module to link everything together.
include(ProjectLinker)

# create an executable
add_executable( ${PROJECT_NAME} main.cpp )

# link the executable together
target_link_libraries( ${PROJECT_NAME} )
