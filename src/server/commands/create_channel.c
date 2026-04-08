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

static channel_data_t *get_channel(server_t *server, team_data_t *team)
{
    char *name_uuid = NULL;
    char *description_uuid = NULL;
    text_data_t *name = NULL;
    text_data_t *description = NULL;
    channel_data_t *channel = NULL;

    name_uuid = get_arg(server->buffer, 2);
    if (name_uuid == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return NULL;
    }
    description_uuid = get_arg(server->buffer, 3);
    if (description_uuid == NULL) {
        free(name_uuid);
        WRITE_STATUS(*CLIENT->fd, 460);
        return NULL;
    }
    name = texts_consume(server->texts, name_uuid);
    description = texts_consume(server->texts, description_uuid);
    free(name_uuid);
    free(description_uuid);
    channel = channels_get_from_name(team->channels, name->body);
    if (channel != NULL) {
        text_data_free(name);
        text_data_free(description);
        WRITE_STATUS(*CLIENT->fd, 440);
        return NULL;
    }
    channel = team_add_channel(team, name->body, description->body);
    text_data_free(name);
    text_data_free(description);
    return channel;
}

// TODO: not respecting protocol here
// Same as LOGIN
void command_create_channel(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    team_data_t *team = teams_get_from_uuid(server->teams, team_uuid);
    channel_data_t *channel = NULL;

    free(team_uuid);
    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    channel = get_channel(server, team);
    if (channel == NULL)
        return;
    WRITE_STATUS(*CLIENT->fd, 200);
    server_event_channel_created(team->uuid, channel->uuid, channel->name);
    send_event_all_clients(server, channel);
}
