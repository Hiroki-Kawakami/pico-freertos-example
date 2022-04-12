# Raspberry Pi Pico FreeRTOS Example

Use FreeRTOS on Raspberry Pi Pico

# Get this example

```
$ git clone https://github.com/Hiroki-Kawakami/pico-freertos-example
$ cd pico-freertos-example
$ git submodule update --init
```

# Build

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Flash `build/example/example.uf2` to your pico!

# References

[yunkya2/pico-freertos-sample: Raspberry Pi Pico Sample application with FreeRTOS](https://github.com/yunkya2/pico-freertos-sample)
[FreeRTOS-SMP-Demos/FreeRTOS/Demo/CORTEX_M0+_RP2040 at main · FreeRTOS/FreeRTOS-SMP-Demos](https://github.com/FreeRTOS/FreeRTOS-SMP-Demos/tree/main/FreeRTOS/Demo/CORTEX_M0%2B_RP2040)