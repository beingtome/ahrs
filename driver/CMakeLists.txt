add_subdirectory(baro)
add_subdirectory(imu)
add_subdirectory(magn)

file(GLOB SRCS
    *.c
)

target_sources(lib_driver INTERFACE
    ${SRCS}
)

target_include_directories(lib_driver INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
