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

// TODO: better command matching, using this TEAM and TEAMS instructions collide.
// Returns true if the command is valid and could stop the loop
// TODO: correct args_amount handling
static bool verify_command(server_t *server, int i)
{
    if (strcmp_start(server->buffer, cmds[i].command) == 0) {
        if (cmds[i].needs_auth == true && CLIENT->login_step == LOGGED_OUT) {
            WRITE_STATUS(*CLIENT->fd, 435);
            return true;
        }
        if (cmds[i].args_amount != strccount(server->buffer, ' ')) {
            WRITE_STATUS(*CLIENT->fd, 499);
            return true;
        }
        cmds[i].function(server);
        return true;
    }
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
