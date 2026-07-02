file(GLOB SRCS
    *.c
)

target_sources(lib_app INTERFACE
    ${SRCS}
)

target_include_directories(lib_app INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

