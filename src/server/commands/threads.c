/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** threads.c
*/

#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void command_threads(server_t *server)
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
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    for (unsigned int i = 0; i < channel->threads->amount; i++) {
        thread = channel->threads->threads[i];
        dprintf(*CLIENT->fd, "%s %s %ld %ld %ld %s %s\n", thread->uuid,
            thread->user_uuid, thread->timestamp,
            strlen(thread->title), strlen(thread->description),
            thread->title, thread->description);
    }
}
