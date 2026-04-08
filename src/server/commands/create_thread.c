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
        dprintf(*CLIENT_I(i)->fd, NEW_THREAD" %s %s %s %ld %s"CRLF,
            thread->uuid, thread->user_uuid, thread->title,
            thread->timestamp, thread->description);
    }
}

static thread_data_t *get_thread(server_t *server, channel_data_t *channel)
{
    char *title_text_uuid = get_arg(server->buffer, 3);
    char *description_text_uuid = get_arg(server->buffer, 4);
    text_data_t *title = NULL;
    text_data_t *description = NULL;
    thread_data_t *thread = NULL;

    if (title_text_uuid == NULL)
        return NULL;
    if (description_text_uuid == NULL) {
        free(title_text_uuid);
        return NULL;
    }
    free(description_text_uuid);
    title = texts_consume(server->texts, title_text_uuid);
    description = texts_consume(server->texts, description_text_uuid);
    free(title_text_uuid);
    free(description_text_uuid);
    thread = channel_add_thread(channel, CLIENT->user->uuid, title->body, description->body);
    text_data_free(title);
    text_data_free(description);
    return thread;
}

// TODO: not respecting protocol here
// Same as LOGIN
void command_create_thread(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *channel_uuid = NULL;
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
    thread = get_thread(server, channel);
    if (thread == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    server_event_thread_created(channel->uuid, thread->uuid, CLIENT->user->uuid,
        thread->title, thread->description);
    send_event_all_clients(server, thread);
}
