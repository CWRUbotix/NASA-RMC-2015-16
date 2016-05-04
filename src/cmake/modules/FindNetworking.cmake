find_path( NETWORKING_INCLUDES Networking/CommTransmitter.hpp
    HINTS
        ${CMAKE_PREFIX_PATH}/include
)

# find libraries depending on OS.
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    # handle dll AND lib?
    find_path( NETWORKING_SHARED_LIB Networking.dll
        HINTS
            ${CMAKE_PREFIX_PATH}/bin
    )
    find_library( NETWORKING_LIB Networking
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
else()
    find_library( NETWORKING_SHARED_LIB Networking
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
endif()

if( NOT NETWORKING_INCLUDES OR NOT NETWORKING_SHARED_LIB )
    set( NETWORKING_FOUND FALSE )
else()
    # set( ASYNC_SHARED_LIB ${ASYNC_SHARED_LIB}/Async.dll )
    set( NETWORKING_FOUND TRUE )
endif()