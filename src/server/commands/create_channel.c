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
        dprintf(*CLIENT_I(i)->fd, NEW_CHANNEL" %s %ld %ld %s %s"CRLF,
            channel->uuid, strlen(channel->name), strlen(channel->description),
            channel->name, channel->description);
    }
}

// TODO: not respecting protocol here
// Same as LOGIN
void command_create_channel(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *name_len_text = NULL;
    int name_len;
    char *name = NULL;
    char *description_len_text = NULL;
    int description_len;
    char *description = NULL;
    team_data_t *team = teams_get_from_uuid(server->teams, team_uuid);
    channel_data_t *channel = NULL;

    free(team_uuid);
    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }

    name_len_text = get_arg(server->buffer, 2);
    if (name_len_text == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    name_len = atoi(name_len_text);
    free(name_len_text);

    description_len_text = get_arg(server->buffer, 3);
    if (description_len_text == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    description_len = atoi(description_len_text);
    free(description_len_text);

    name = read_bytes_starting_arg(server->buffer, 4, name_len);
    description = read_bytes_starting_arg(server->buffer, 4, name_len + 1 + description_len);

    channel = channels_get_from_name(team->channels, name);
    if (channel != NULL) {
        free(name);
        WRITE_STATUS(*CLIENT->fd, 440);
        return;
    }
    channel = team_add_channel(team, name, description + name_len + 1);
    free(name);
    free(description);
    WRITE_STATUS(*CLIENT->fd, 200);
    server_event_channel_created(team->uuid, channel->uuid, channel->name);
    send_event_all_clients(server, channel);
}
