find_path( COMMUNICATIONS_INCLUDES Communications/CommTransmitter.hpp
    HINTS
        ${CMAKE_PREFIX_PATH}/include
)

# find libraries depending on OS.
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    # handle dll AND lib?
    find_path( COMMUNICATIONS_SHARED_LIB Networking.dll
        HINTS
            ${CMAKE_PREFIX_PATH}/bin
    )
    find_library( COMMUNICATIONS_LIB Networking
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
else()
    find_library( COMMUNICATIONS_SHARED_LIB Networking
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
endif()

if( NOT COMMUNICATIONS_INCLUDES OR NOT COMMUNICATIONS_SHARED_LIB )
    set( COMMUNICATIONS_FOUND FALSE )
else()
    # set( ASYNC_SHARED_LIB ${ASYNC_SHARED_LIB}/Async.dll )
    set( COMMUNICATIONS_FOUND TRUE )
endif()
