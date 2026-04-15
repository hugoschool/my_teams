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
                char *team_uuid = get_arg(second_recv, 0);
                char *team_name_len = get_arg(second_recv, 1);
                char *team_desc_len = get_arg(second_recv, 2);
                char *team_name = read_bytes_starting_arg(second_recv, 3, atoi(team_name_len));
                char *team_desc = read_bytes_starting_arg(second_recv, 3, atoi(team_name_len) + 1 + atoi(team_desc_len));
                client_print_teams(team_uuid, team_name, team_desc + 1 + atoi(team_name_len));
                super_free(5, team_uuid, team_name, team_name_len, team_desc, team_desc_len);
                break;
            }
            case TEAM: {
                char *channel_uuid = get_arg(second_recv, 0);
                char *channel_name_len = get_arg(second_recv, 1);
                char *channel_desc_len = get_arg(second_recv, 2);
                char *channel_name = read_bytes_starting_arg(second_recv, 3, atoi(channel_name_len));
                char *channel_desc = read_bytes_starting_arg(second_recv, 3, atoi(channel_name_len) + 1 + atoi(channel_desc_len));
                client_team_print_channels(channel_uuid, channel_name, channel_desc + 1 + atoi(channel_desc_len));
                super_free(5, channel_uuid, channel_name_len, channel_name, channel_desc_len, channel_desc);
                break;
            }
            case CHANNEL: {
                char *thread_uuid = get_arg(second_recv, 0);
                char *user_uuid = get_arg(second_recv, 1);
                char *thread_timestamp = get_arg(second_recv, 2);
                char *thread_title_len = get_arg(second_recv, 3);
                char *thread_desc_len = get_arg(second_recv, 4);
                char *thread_desc = read_bytes_starting_arg(second_recv, 5, atoi(thread_title_len) + 1 + atoi(thread_desc_len));
                char *thread_title = read_bytes_starting_arg(second_recv, 5, atoi(thread_title_len));
                client_channel_print_threads(thread_uuid, user_uuid, atoi(thread_timestamp), thread_title, thread_desc + 1 + atoi(thread_title_len));
                super_free(7, thread_uuid, user_uuid, thread_timestamp, thread_title_len, thread_desc, thread_desc_len, thread_title);
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
