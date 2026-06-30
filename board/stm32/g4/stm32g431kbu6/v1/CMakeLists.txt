set(BOARD   ${CMAKE_CURRENT_LIST_DIR})
set(CUBEMX  ${BOARD}/cubemx/board)

set(HAL     ${BOARD}/../../STM32G4xx_HAL_Driver)
set(CMSIS   ${BOARD}/../../../CMSIS)
set(LDSCRIPT ${BOARD}/linker/STM32G431XX_FLASH.ld)

set(MCU_FLAGS
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -mthumb
)

target_compile_options(lib_board INTERFACE
    ${MCU_FLAGS}
    -Wall
    -Wextra
    -Werror
    -Wno-cast-function-type
    -Wno-sign-compare
    -Wshadow
    -Wundef
    -Wformat=2
    -Wpointer-arith
    -Winit-self
    -Wno-unused-parameter
    -Wno-missing-field-initializers
    -Os
    -g
    -ffunction-sections
    -fdata-sections
    -fno-common
    -fno-strict-aliasing
    -fomit-frame-pointer
    -flto
)

target_compile_definitions(lib_board INTERFACE
    STM32G431xx
    USE_HAL_DRIVER
)

target_include_directories(lib_board INTERFACE
    ${BOARD}
    ${BOARD}/hal
    ${CUBEMX}/Core/Inc
    ${CUBEMX}/USB_Device/App
    ${CUBEMX}/USB_Device/Target
    ${CUBEMX}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ${CUBEMX}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    ${HAL}/Inc
    ${CMSIS}/Core
    ${CMSIS}/Device/ST/STM32G4xx/Include
    ${CMSIS}/Include
    ${CMAKE_BINARY_DIR}

    # kconfig
    ${CMAKE_BINARY_DIR}/generated
)

target_link_options(lib_board INTERFACE
    ${MCU_FLAGS}
    -T${LDSCRIPT}
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
    -flto
    --specs=nano.specs
    --specs=nosys.specs
    -lc
    -lm
)

file(GLOB_RECURSE SRCS
    ${BOARD}/*.c
    ${BOARD}/startup/*.s
    ${CUBEMX}/Core/Src/*.c
    ${CUBEMX}/USB_Device/App/*.c
    ${CUBEMX}/USB_Device/Target/*.c
    ${CUBEMX}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/*.c
    ${CUBEMX}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/*.c
    ${HAL}/Src/*.c
)

list(FILTER SRCS EXCLUDE REGEX ".*_template\.c$")

target_sources(lib_board INTERFACE ${SRCS})
