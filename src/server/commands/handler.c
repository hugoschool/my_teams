/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** handler.c
*/

#include "server/commands.h"
#include "server/server.h"
#include "utils.h"
#include <stdbool.h>

// TODO: better command matching, using this TEAM and TEAMS instructions collide.
// Returns true if the command is valid and could stop the loop
static bool verify_command(server_t *server, char *buffer, int i)
{
    if (strcmp_start(buffer, cmds[i].command) == 0) {
        if (cmds[i].needs_auth == true && CLIENT->login_step == LOGGED_OUT) {
            // TODO: handle this status code
            return true;
        }
        cmds[i].function(server);
        return true;
    }
    return false;
}

// TODO: when no comment is found, send status code error
void commands_handler(server_t *server, char *buffer)
{
    if (strcmp_end(buffer, CRLF) != 0)
        return;
    for (int cmd_i = 0; cmds[cmd_i].command != NULL; cmd_i++) {
        if (verify_command(server, buffer, cmd_i))
            return;
    }
}
