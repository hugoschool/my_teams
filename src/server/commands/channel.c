/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** channel.c
*/

#include "server/commands.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdlib.h>

void command_channel(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *uuid = NULL;
    team_data_t *team = NULL;
    channel_data_t *channel = NULL;

    if (team_uuid == NULL)
        return;
    team = teams_get_from_uuid(server->teams, team_uuid);
    free(team_uuid);
    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 461);
        return;
    }
    uuid = get_arg(server->buffer, 2);
    channel = channels_get_from_uuid(team->channels, uuid);
    free(uuid);
    if (channel == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    channel_print(*CLIENT->fd, channel, 200);
}
