#include "client/client.h"
#include "client/commands.h"
#include <stdio.h>

void command_parser(char *command, client_t *client)
{
    printf("%s\n", client->context.team_uuid);
    for (int i = 0; commands[i].cmd != NULL; i++) {
        if (strncmp(command, commands[i].cmd, strlen(commands[i].cmd)) == 0) {
            if (commands[i].func && arg_amount_quote(command) - 1 >= commands[i].nb_args) {
                commands[i].func(command, client);
                continue;
            }
            dprintf(STDERR_FILENO, "Unknown command\n");
        }
    }
}
