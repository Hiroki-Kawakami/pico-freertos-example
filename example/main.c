#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

static void blink_task(void *pvParameters) {
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    bool isOn = false;
    while (true) {
        gpio_put(25, isOn = !isOn);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void console_task(void *pvParameters);

int main() {
    stdio_init_all();

    xTaskCreate(blink_task, "blink", 256, NULL, 1, NULL);

    xTaskCreate(console_task, "console", 1024, NULL, 1, NULL);

    vTaskStartScheduler();

    while (true);
}