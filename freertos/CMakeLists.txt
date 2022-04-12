add_library(freertos)
target_include_directories(freertos PUBLIC
    ${FREERTOS_SOURCE_PATH}
)
target_link_libraries(freertos
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap3
    pico_stdlib
)