cmake_minimum_required(VERSION 3.13)

set(FREERTOS_SOURCE_PATH ${CMAKE_CURRENT_LIST_DIR}/freertos)
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/freertos/FreeRTOS-Kernel)

include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)

project(pico-freertos-example)

pico_sdk_init()

add_subdirectory(freertos)
add_subdirectory(example)
