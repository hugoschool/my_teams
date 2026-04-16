/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** user.c
*/

#include "server/commands.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdlib.h>

void command_user(server_t *server)
{
    char *uuid = NULL;
    user_data_t *user = NULL;

    uuid = get_arg(server->buffer, 1);
    if (uuid == NULL)
        return;
    user = users_get_from_uuid(server->users, uuid);
    free(uuid);
    if (user == NULL) {
        WRITE_STATUS(*CLIENT->fd, 464);
        return;
    }
    user_print(*CLIENT->fd, user, 200);
}
