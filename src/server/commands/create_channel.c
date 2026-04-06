/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** create_channel.c
*/

#include "logging_server.h"
#include "server/events.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static void send_event_all_clients(server_t *server, channel_data_t *channel)
{
    for (unsigned int i = INITIAL_AMOUNT; i < server->clients->amount; i++) {
        if (i == server->index || CLIENT_I(i)->login_step == LOGGED_OUT)
            continue;
        dprintf(*CLIENT_I(i)->fd, NEW_CHANNEL" %s %s %s"CRLF,
            channel->uuid, channel->name, channel->description);
    }
}

// TODO: not respecting protocol here
// Same as LOGIN
void command_create_channel(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *name = NULL;
    char *description = NULL;
    team_data_t *team = teams_get_from_uuid(server->teams, team_uuid);
    channel_data_t *channel = NULL;

    free(team_uuid);
    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    name = get_arg(server->buffer, 2);
    channel = channels_get_from_name(team->channels, name);
    if (channel != NULL) {
        free(name);
        WRITE_STATUS(*CLIENT->fd, 440);
        return;
    }
    description = get_arg(server->buffer, 3);
    channel = team_add_channel(team, name, description);
    free(name);
    free(description);
    WRITE_STATUS(*CLIENT->fd, 200);
    server_event_channel_created(team->uuid, channel->uuid, channel->name);
    send_event_all_clients(server, channel);
}
