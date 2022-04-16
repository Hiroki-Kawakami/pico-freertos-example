add_executable(example
    prime.c
    Sample-CLI-commands.c
    commands.c
    console.c
    main.c
)
target_link_libraries(example pico_stdlib pico_multicore freertos)
pico_add_extra_outputs(example)
pico_enable_stdio_usb(example 1)
