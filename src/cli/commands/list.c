#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_list_command(client_t *client)
{
    char *cmd = NULL;

    switch (client->context.type) {
        case BASE:
            asprintf(&cmd, TEAM_LIST CRLF);
            break;
        case TEAM:
            asprintf(&cmd, CHANNEL_LIST" %s"CRLF, client->context.team_uuid);
            break;
        case CHANNEL:
            asprintf(&cmd, THREAD_LIST" %s %s"CRLF, client->context.team_uuid, client->context.channel_uuid);
            break;
        case THREAD:
            asprintf(&cmd, COMMENT_LIST" %s %s %s"CRLF, client->context.team_uuid, client->context.channel_uuid, client->context.thread_uuid);
            break;
        default:
            break;
    }
    return cmd;
}

void cmd_list(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    (void)command;
    char *real_cmd = craft_list_command(client);
    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BIG_BUFFER_SIZE);
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    remove_crlf(real_cmd);
    char *saveptr;
    char *second_recv = strtok_r(client->buffer, "\n", &saveptr);
    second_recv = strtok_r(NULL, "\n", &saveptr);
    while (second_recv != NULL) {
        switch (client->context.type) {
            case BASE: {
                team_content_t *team = team_parse_line(second_recv, 0);
                client_print_teams(team->uuid, team->name, team->description);
                team_content_free(team);
                break;
            }
            case TEAM: {
                channel_content_t *channel = channel_parse_line(second_recv, 0);
                client_team_print_channels(channel->uuid, channel->name, channel->description);
                channel_content_free(channel);
                break;
            }
            case CHANNEL: {
                thread_content_t *thread = thread_parse_line(second_recv, 0);
                client_channel_print_threads(thread->thread_uuid, thread->user_uuid, thread->timestamp, thread->title, thread->description);
                thread_content_free(thread);
                break;
            }
            case THREAD: {
                char *thread_uuid = get_arg(second_recv, 0);
                char *user_uuid = get_arg(second_recv, 1);
                char *timestamp = get_arg(second_recv, 2);
                char *body_len = get_arg(second_recv, 3);
                char *body = read_bytes_starting_arg(second_recv, 4, atoi(body_len));
                client_thread_print_replies(thread_uuid, user_uuid, atoi(timestamp), body);
                super_free(5, thread_uuid, user_uuid, timestamp, body_len, body);
                break;
            }
        }
        second_recv = strtok_r(NULL, "\n", &saveptr);
    }
    free(real_cmd);
}
