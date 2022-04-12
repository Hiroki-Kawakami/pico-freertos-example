add_executable(example
    main.c
)
target_link_libraries(example pico_stdlib freertos)
pico_add_extra_outputs(example)
pico_enable_stdio_usb(example 1)
