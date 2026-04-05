/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** unsubscribe_team.c
*/

#include "logging_server.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>

static team_data_t *get_team(server_t *server)
{
    team_data_t *team = NULL;
    char *uuid = get_arg(server->buffer, 1);

    team = teams_get_from_uuid(server->teams, uuid);
    free(uuid);
    return team;
}

void command_unsubscribe_team(server_t *server)
{
    team_data_t *team = get_team(server);

    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    if (team_is_user_subscribed(team, CLIENT->user) == false) {
        WRITE_STATUS(*CLIENT->fd, 451);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    users_remove_by_data(team->users, CLIENT->user);
    server_event_user_unsubscribed(team->uuid, CLIENT->user->uuid);
}
