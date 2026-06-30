cmake_minimum_required(VERSION 3.16)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER    arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_OBJCOPY       arm-none-eabi-objcopy)
set(CMAKE_SIZE          arm-none-eabi-size)

project(ahrs C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ---- INTERFACE 壳 ----
add_library(lib_board INTERFACE)
add_library(lib_lib INTERFACE)
add_library(lib_driver INTERFACE)
add_library(lib_app INTERFACE)

# ---- 各层填充 ----
add_subdirectory(board)
add_subdirectory(lib)
add_subdirectory(driver)
add_subdirectory(app)

# ---- elf ----
add_executable(${PROJECT_NAME}.elf)
target_link_libraries(${PROJECT_NAME}.elf PRIVATE
    lib_board
    lib_lib
    lib_driver
    lib_app
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex  $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
)
