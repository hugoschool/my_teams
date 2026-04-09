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
        dprintf(*CLIENT_I(i)->fd, NEW_THREAD" %s %s %ld %ld %ld %s %s"CRLF,
            thread->uuid, thread->user_uuid, thread->timestamp,
            strlen(thread->title), strlen(thread->description),
            thread->title, thread->description);
    }
}

void command_create_thread(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *channel_uuid = NULL;
    char *title_len_text = NULL;
    int title_len = 0;
    char *title = NULL;
    char *description_len_text = NULL;
    int description_len = 0;
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

    title_len_text = get_arg(server->buffer, 3);
    if (title_len_text == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    title_len = atoi(title_len_text);
    free(title_len_text);

    description_len_text = get_arg(server->buffer, 4);
    if (description_len_text == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    description_len = atoi(description_len_text);
    free(description_len_text);

    title = read_bytes_starting_arg(server->buffer, 5, title_len);
    description = read_bytes_starting_arg(server->buffer, 5, title_len + 1 + description_len);

    thread = channel_add_thread(channel, CLIENT->user->uuid, title, description + title_len + 1);
    free(title);
    free(description);
    WRITE_STATUS(*CLIENT->fd, 200);
    server_event_thread_created(channel->uuid, thread->uuid, CLIENT->user->uuid,
        thread->title, thread->description);
    send_event_all_clients(server, thread);
    dprintf(*CLIENT->fd, "%s %s %ld %ld %ld %s %s\n", thread->uuid,
        thread->user_uuid, thread->timestamp,
        strlen(thread->title), strlen(thread->description),
        thread->title, thread->description);
}
