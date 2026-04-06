/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** channels.c
*/

#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void command_channels(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    team_data_t *team = teams_get_from_uuid(server->teams, team_uuid);
    channel_data_t *channel = NULL;

    free(team_uuid);
    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    for (unsigned int i = 0; i < team->channels->amount; i++) {
        channel = team->channels->channels[i];
        dprintf(*CLIENT->fd, "%s %s %s\n", channel->name, channel->uuid,
            channel->description);
    }
}
