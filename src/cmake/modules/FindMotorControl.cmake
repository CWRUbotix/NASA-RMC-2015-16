find_path( MOTORCONTROL_INCLUDES MotorControl/MotorControlNode.hpp
    HINTS
        ${CMAKE_PREFIX_PATH}/include
)

# find libraries depending on OS.
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    # handle dll AND lib?
    find_path( MOTORCONTROL_SHARED_LIB MotorControl.dll
        HINTS
            ${CMAKE_PREFIX_PATH}/bin
    )
    find_library( MOTORCONTROL_LIB MotorControl
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
else()
    find_library( MOTORCONTROL_SHARED_LIB MotorControl
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
endif()

if( NOT MOTORCONTROL_INCLUDES OR NOT MOTORCONTROL_SHARED_LIB )
    set( MOTORCONTROL_FOUND FALSE )
else()
    # set( ASYNC_SHARED_LIB ${ASYNC_SHARED_LIB}/Async.dll )
    set( MOTORCONTROL_FOUND TRUE )
endif()
