#include "client/client.h"
#include "client/commands.h"
#include <stdio.h>
#include <stdlib.h>

void command_parser(char *command, client_t *client)
{
    char *cmd_cmp = get_arg(command, 0);

    for (int i = 0; commands[i].cmd != NULL; i++) {
        if (strncmp(cmd_cmp, commands[i].cmd, strlen(commands[i].cmd)) == 0) {
            if (arg_amount_quote(command) >= commands[i].nb_args) {
                commands[i].func(command, client);
                free(cmd_cmp);
                return;
            }
        }
    }
    dprintf(STDOUT_FILENO, "%s: Unknown command. Use /help to see which commands are available.\n", cmd_cmp);
    free(cmd_cmp);
}
