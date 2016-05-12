find_path( ADC_INCLUDES ADC/ADC.hpp
    HINTS
        ${CMAKE_PREFIX_PATH}/include
)

# find libraries depending on OS.
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    # handle dll AND lib?
    find_path( ADC_SHARED_LIB ADC.dll
        HINTS
            ${CMAKE_PREFIX_PATH}/bin
    )
    find_library( ADC_LIB ADC
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
else()
    find_library( ADC_SHARED_LIB ADC
        HINTS
            ${CMAKE_PREFIX_PATH}/lib
    )
endif()

if( NOT ADC_INCLUDES OR NOT ADC_SHARED_LIB )
    set( ADC_FOUND FALSE )
else()
    # set( ASYNC_SHARED_LIB ${ASYNC_SHARED_LIB}/Async.dll )
    set( ADC_FOUND TRUE )
endif()
