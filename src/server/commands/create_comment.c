/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** create_comment.c
*/

#include "logging_server.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdlib.h>

// TODO: not respecting protocol here
// Same as LOGIN
void command_create_comment(server_t *server)
{
    char *team_uuid = get_arg(server->buffer, 1);
    char *channel_uuid = NULL;
    char *thread_uuid = NULL;
    char *body = NULL;
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
        WRITE_STATUS(*CLIENT->fd, 440);
        return;
    }
    thread_uuid = get_arg(server->buffer, 3);
    thread = threads_get_from_uuid(channel->threads, thread_uuid);
    free(thread_uuid);
    if (thread == NULL) {
        WRITE_STATUS(*CLIENT->fd, 440);
        return;
    }
    body = get_arg(server->buffer, 4);
    WRITE_STATUS(*CLIENT->fd, 200);
    comment = thread_add_comment(thread, CLIENT->user->uuid, body);
    server_event_reply_created(thread->uuid, CLIENT->user->uuid, comment->body);
    free(body);
}
