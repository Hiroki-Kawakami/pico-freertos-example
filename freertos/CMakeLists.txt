add_library(freertos)
target_sources(freertos PUBLIC
    FreeRTOS-Plus-CLI/FreeRTOS_CLI.c
)
target_include_directories(freertos PUBLIC
    ${FREERTOS_SOURCE_PATH}
    FreeRTOS-Plus-CLI
)
target_link_libraries(freertos
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap3
    pico_stdlib
)