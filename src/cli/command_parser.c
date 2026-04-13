#include "client/client.h"
#include "client/commands.h"
#include <stdio.h>

void command_parser(char *command, client_t *client)
{
    for (int i = 0; commands[i].cmd != NULL; i++) {
        if (strncmp(command, commands[i].cmd, strlen(commands[i].cmd)) == 0) {
            if (commands[i].func && arg_amount_quote(command) >= commands[i].nb_args) {
                commands[i].func(command, client);
                continue;
            }
            dprintf(STDERR_FILENO, "Unknown command. Use /help to see which commands are available.\n");
        }
    }
}
