#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_info_command(const char *context, client_t *client)
{
    char *cmd = NULL;

    if (strcmp(context, NO_CONTEXT) == 0) {
        asprintf(&cmd, "USER %s%s", client->uuid, CRLF);
    } else if (strcmp(context, TEAM_INFO) == 0) {
        asprintf(&cmd, "%s %s%s", context, client->context.team_uuid, CRLF);
    } else if (strcmp(context, CHANNEL_INFO) == 0) {
        asprintf(&cmd, "%s %s %s%s", context, client->context.team_uuid, client->context.channel_uuid, CRLF);
    } else if (strcmp(context, THREAD_INFO) == 0) {
        asprintf(&cmd, "%s %s %s %s%s", context, client->context.team_uuid, client->context.channel_uuid, client->context.thread_uuid, CRLF);
    }
    return cmd;
}

void cmd_info(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    (void)command;
    char *real_cmd = NULL;
    switch (client->context.type) {
        case BASE:
            real_cmd = craft_info_command(NO_CONTEXT, client);
            break;
        case TEAM:
            real_cmd = craft_info_command(TEAM_INFO, client);
            break;
        case CHANNEL:
            real_cmd = craft_info_command(CHANNEL_INFO, client);
            break;
        case THREAD:
            real_cmd = craft_info_command(THREAD_INFO, client);
            break;
    }
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
    switch (client->context.type) {
        case BASE: {
            char *user_uuid = get_arg(second_recv, 1);
            char *user_name = get_arg(second_recv, 0);
            char *status = get_arg(second_recv, 2);
            client_print_user(user_uuid, user_name, atoi(status));
            super_free(3, user_name, user_uuid, status);
            break;
        }
        case TEAM: {
            team_content_t *team = team_parse_line(second_recv, 0);
            client_print_team(team->uuid, team->name, team->description);
            team_content_free(team);
            break;
        }
        case CHANNEL: {
            channel_content_t *channel = channel_parse_line(second_recv, 0);
            client_print_channel(channel->uuid, channel->name, channel->description);
            channel_content_free(channel);
            break;
        }
        case THREAD: {
            thread_content_t *thread = thread_parse_line(second_recv, 0);
            client_print_thread(thread->thread_uuid, thread->user_uuid, thread->timestamp, thread->title, thread->description);
            thread_content_free(thread);
            break;
        }
    }
    free(real_cmd);
}
