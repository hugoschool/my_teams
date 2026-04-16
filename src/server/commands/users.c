/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** users.c
*/

#include "server/commands.h"
#include "server/server.h"
#include "server/status.h"
#include <stdio.h>

void command_users(server_t *server)
{
    user_data_t *user = NULL;

    WRITE_STATUS(*CLIENT->fd, 200);
    for (unsigned int i = 0; i < server->users->amount; i++) {
        user = USER_I(i);
        user_print(*CLIENT->fd, user, 0);
    }
}
