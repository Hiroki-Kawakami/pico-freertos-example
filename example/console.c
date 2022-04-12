#include <FreeRTOS.h>
#include <FreeRTOS_CLI.h>
#include <task.h>
#include <stdio.h>

static const char * const cliPrefix = "cli> ";

void vRegisterSampleCLICommands( void );

void console_task(void *pvParameters) {
    int inputOffset = 0;
    char inputBuffer[256] = {};
    char *outputBuffer;
    BaseType_t hasNextOutput;

    vRegisterSampleCLICommands();
    outputBuffer = FreeRTOS_CLIGetOutputBuffer();

    printf("%s", cliPrefix);

    while (true) {
        char c = getchar();
        if (c == '\r' || c == '\n') {
            printf("\n");
            if (inputOffset != 0) {
                inputBuffer[inputOffset++] = '\0';
                do {
                    hasNextOutput = FreeRTOS_CLIProcessCommand(inputBuffer, outputBuffer, configCOMMAND_INT_MAX_OUTPUT_SIZE);
                    printf("%s", outputBuffer);
                } while(hasNextOutput != pdFALSE);
                inputOffset = 0;
            }
            printf("%s", cliPrefix);
        } else if (c == '\b' || c == 0x7F) {
            if (inputOffset == 0) continue;
            inputBuffer[--inputOffset] = '\0';
            printf("\33[2K\r%s%s", cliPrefix, inputBuffer);
        } else {
            if (c < 0x20 || c > 0x7e) continue; // Not ASCII Character
            if (inputOffset >= sizeof(inputBuffer) - 1) continue; // Out of buffer
            inputBuffer[inputOffset++] = c;
            printf("%c", c);
        }
    }
}