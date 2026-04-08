/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** thread.c
*/

#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void command_thread(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *channel_uuid = NULL;
    char *uuid = NULL;
    team_data_t *team = NULL;
    channel_data_t *channel = NULL;
    thread_data_t *thread = NULL;

    if (team_uuid == NULL)
        return;
    team = teams_get_from_uuid(server->teams, team_uuid);
    free(team_uuid);
    if (team == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    channel_uuid = get_arg(server->buffer, 2);
    channel = channels_get_from_uuid(team->channels, channel_uuid);
    free(channel_uuid);
    if (channel == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    uuid = get_arg(server->buffer, 3);
    thread = threads_get_from_uuid(channel->threads, uuid);
    free(uuid);
    if (thread == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    dprintf(*CLIENT->fd, "%s %s %ld %ld %ld %s %s\n", thread->uuid,
        thread->user_uuid, thread->timestamp,
        strlen(thread->title), strlen(thread->description),
        thread->title, thread->description);
}
