file(GLOB SRCS
    *.c
)

target_sources(lib_middleware INTERFACE
    ${SRCS}
)

target_include_directories(lib_middleware INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
