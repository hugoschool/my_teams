/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** comments.c
*/

#include "server/commands.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdlib.h>

void command_comments(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *channel_uuid = NULL;
    char *thread_uuid = NULL;
    team_data_t *team = teams_get_from_uuid(server->teams, team_uuid);
    channel_data_t *channel = NULL;
    thread_data_t *thread = NULL;
    comment_data_t *comment = NULL;

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
    thread_uuid = get_arg(server->buffer, 3);
    thread = threads_get_from_uuid(channel->threads, thread_uuid);
    free(thread_uuid);
    if (thread == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    for (unsigned int i = 0; i < thread->comments->amount; i++) {
        comment = thread->comments->comments[i];
        comment_print(*CLIENT->fd, comment);
    }
}
