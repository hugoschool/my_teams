/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** list_subscribed_users.c
*/

#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static team_data_t *get_team(server_t *server)
{
    team_data_t *team = NULL;
    char *uuid = get_arg(server->buffer, 1);

    team = teams_get_from_uuid(server->teams, uuid);
    free(uuid);
    return team;
}

void command_list_subscribed_users(server_t *server)
{
    team_data_t *team = get_team(server);
    user_data_t *user = NULL;

    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    for (unsigned int i = 0; i < team->users->amount; i++) {
        user = team->users->users[i];
        dprintf(*CLIENT->fd, "%s %s %d\n", user->username, user->uuid,
            user->status);
    }
}
