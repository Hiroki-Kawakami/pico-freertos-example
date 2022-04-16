#include <FreeRTOS.h>
#include <FreeRTOS_CLI.h>
#include <task.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"

void prime_calc(int max) {
    TickType_t start = xTaskGetTickCount();
    int count = 0;
    int i, j;
    for (i = 2; i <= max; i++) {
        for (j = 2; j < i; j++) {
            if (i % j == 0) break;
        }
        if (i == j) {
            count++;
        }
    }
    TickType_t end = xTaskGetTickCount();
#if configUSE_CORE_AFFINITY == 1
    int core = (vTaskCoreAffinityGet(NULL) != (1 << 0)) ? 1 : 0;
    printf("\n%d prime numbers found!\n", count);
    printf("Finish! %d Tick (Core %d)\n", end - start, core);
#else
    printf("Finish! %d Tick\n", end - start);
#endif
}

static void prime_calc_task(void *pvParameters) {
    prime_calc(*(int*)pvParameters);
    vPortFree(pvParameters);
    vTaskDelete(NULL);
}

void prime_start_calc_task(int cpu, int max) {
    int *param = (int*)pvPortMalloc(sizeof(int));
    *param = max;
    TaskHandle_t task;
    xTaskCreate(prime_calc_task, "prime", 1024, param, 1, &task);
#if configUSE_CORE_AFFINITY == 1
    vTaskCoreAffinitySet(task, 1 << cpu);
#endif
}

BaseType_t prime_command_interpreter(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    BaseType_t subcmd_len;
    const char *subcmd = FreeRTOS_CLIGetParameter(pcCommandString, 1, &subcmd_len);
    const char *max_str = FreeRTOS_CLIGetParameter(pcCommandString, 2, NULL);
    int max = atoi(max_str);
    
    if (!strncmp(subcmd, "once", subcmd_len)) {
        sprintf(pcWriteBuffer, "Start 1 task\r\n");
        prime_start_calc_task(0, max);
        return pdFALSE;
    }
    if (!strncmp(subcmd, "single", subcmd_len)) {
        prime_start_calc_task(0, max);
        prime_start_calc_task(0, max);
        sprintf(pcWriteBuffer, "Start 2 task on single core\r\n");
        return pdFALSE;
    }
    if (!strncmp(subcmd, "multi", subcmd_len)) {
        prime_start_calc_task(0, max);
        prime_start_calc_task(1, max);
        sprintf(pcWriteBuffer, "Start 2 task on each core\r\n");
        return pdFALSE;
    }

    sprintf(pcWriteBuffer, "Unknown subcmd %s\r\n", subcmd);
    return pdFALSE;
}
