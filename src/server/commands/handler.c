/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** handler.c
*/

#include "server/commands.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>

// Returns true if the command is valid and could stop the loop
static bool verify_command(server_t *server, int i)
{
    char *command = get_arg(server->buffer, 0);

    if (strncmp(command, cmds[i].command, strlen(cmds[i].command)) == 0) {
        free(command);
        if (cmds[i].needs_auth == true && CLIENT->login_step == LOGGED_OUT) {
            WRITE_STATUS(*CLIENT->fd, 435);
            return true;
        }
        if (cmds[i].args_amount >= 0 &&
            (const size_t)cmds[i].args_amount != arg_amount(server->buffer) - 1) {
            WRITE_STATUS(*CLIENT->fd, 499);
            return true;
        }
        cmds[i].function(server);
        return true;
    }
    free(command);
    return false;
}

void commands_handler(server_t *server)
{
    if (strcmp_end(server->buffer, CRLF) != 0)
        return;
    remove_crlf(server->buffer);
    for (int cmd_i = 0; cmds[cmd_i].command != NULL; cmd_i++) {
        if (verify_command(server, cmd_i))
            return;
    }
    WRITE_STATUS(*CLIENT->fd, 499);
}
