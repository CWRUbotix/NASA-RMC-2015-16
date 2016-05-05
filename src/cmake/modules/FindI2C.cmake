find_path( I2C_INCLUDES I2C/I2C.hpp
    HINTS
        ${CMAKE_PREFIX_PATH}/include
)

# find libraries depending on OS.
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    # handle dll AND lib?
    find_path( I2C_SHARED_LIB I2C.dll
        HINTS
            ${CMAKE_PREFIX_PATH}/bin
    )
    find_library( I2C_LIB I2C
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
else()
    find_library( I2C_SHARED_LIB I2C
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
endif()

if( NOT I2C_INCLUDES OR NOT I2C_SHARED_LIB )
    set( I2C_FOUND FALSE )
else()
    # set( ASYNC_SHARED_LIB ${ASYNC_SHARED_LIB}/Async.dll )
    set( I2C_FOUND TRUE )
endif()
