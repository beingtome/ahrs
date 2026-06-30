file(GLOB SRCS
    *.c
)

target_sources(lib_lib INTERFACE
    ${SRCS}
)

target_include_directories(lib_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
