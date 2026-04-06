/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** create_thread.c
*/

#include "logging_server.h"
#include "server/events.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static void send_event_all_clients(server_t *server, thread_data_t *thread)
{
    for (unsigned int i = INITIAL_AMOUNT; i < server->clients->amount; i++) {
        if (i == server->index || CLIENT_I(i)->login_step == LOGGED_OUT)
            continue;
        dprintf(*CLIENT_I(i)->fd, NEW_THREAD" %s %s %s %ld"CRLF,
            thread->uuid, thread->title, thread->description, thread->timestamp);
    }
}

// TODO: not respecting protocol here
// Same as LOGIN
void command_create_thread(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *channel_uuid = NULL;
    char *title = NULL;
    char *description = NULL;
    team_data_t *team = teams_get_from_uuid(server->teams, team_uuid);
    channel_data_t *channel = NULL;
    thread_data_t *thread = NULL;

    free(team_uuid);
    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    channel_uuid = get_arg(server->buffer, 2);
    channel = channels_get_from_uuid(team->channels, channel_uuid);
    free(channel_uuid);
    if (channel == NULL) {
        WRITE_STATUS(*CLIENT->fd, 440);
        return;
    }
    title = get_arg(server->buffer, 3);
    description = get_arg(server->buffer, 4);
    thread = channel_add_thread(channel, title, description);
    free(title);
    free(description);
    WRITE_STATUS(*CLIENT->fd, 200);
    server_event_thread_created(channel->uuid, thread->uuid, CLIENT->user->uuid,
        thread->title, thread->description);
    send_event_all_clients(server, thread);
}
