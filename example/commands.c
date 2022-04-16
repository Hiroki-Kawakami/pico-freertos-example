#include <FreeRTOS.h>
#include <FreeRTOS_CLI.h>
#include <task.h>
#include <stdio.h>

void vRegisterSampleCLICommands( void );
BaseType_t prime_command_interpreter(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

static const CLI_Command_Definition_t commands[] = {
    {
        "prime",
        "\r\nprime [single|multi] <max>:"
        "\r\n Calculate prime numbers in single/multi thread."
        "\r\n\r\n",
        prime_command_interpreter,
        2
    },
};
#define CLI_COMMAND_COUNT (sizeof(commands) / sizeof(CLI_Command_Definition_t))

void cli_register_commands() {
    vRegisterSampleCLICommands();
    for (int i = 0, n = CLI_COMMAND_COUNT; i < n; i++) {
        FreeRTOS_CLIRegisterCommand(&commands[i]);	
    } 
}