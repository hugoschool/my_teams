#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_create_command(char *command, client_t *client)
{
    char *cmd = NULL;
    char name[MAX_NAME_LENGTH] = {0};
    char desc[MAX_DESCRIPTION_LENGTH] = {0};
    char *name_ = NULL;
    char *description = NULL;

    if (command[strlen(command) - 1] == '\n')
        command[strlen(command) - 1] = '\0';
    switch (client->context.type) {
        case BASE: {
            name_ = get_arg_quote(command, 1);
            description = get_arg_quote(command, 3);
            strncpy(name, name_, MAX_NAME_LENGTH);
            strncpy(desc, description, MAX_DESCRIPTION_LENGTH);
            asprintf(&cmd, CREATE_TEAM" %lu %lu %s %s"CRLF, strlen(name), strlen(desc), name, desc);
            break;
        }
        case TEAM: {
            name_ = get_arg_quote(command, 1);
            description = get_arg_quote(command, 3);
            strncpy(name, name_, MAX_NAME_LENGTH);
            strncpy(desc, description, MAX_DESCRIPTION_LENGTH);
            asprintf(&cmd, CREATE_CHANNEL" %s %lu %lu %s %s"CRLF, client->context.team_uuid, strlen(name), strlen(desc), name, desc);
            break;
        }
        case CHANNEL: {
            name_ = get_arg_quote(command, 1);
            description = get_arg_quote(command, 3);
            strncpy(name, name_, MAX_NAME_LENGTH);
            strncpy(desc, description, MAX_DESCRIPTION_LENGTH);
            asprintf(&cmd, CREATE_THREAD" %s %s %lu %lu %s %s"CRLF, client->context.team_uuid, client->context.channel_uuid, strlen(name), strlen(desc), name, desc);
            break;
        }
        case THREAD: {
            char body[MAX_BODY_LENGTH] = {0};
            char *body_ = get_arg_quote(command, 1);
            strncpy(body, body_, MAX_BODY_LENGTH);
            asprintf(&cmd, "%s %s %s %s %lu %s%s", CREATE_COMMENT, client->context.team_uuid, client->context.channel_uuid, client->context.thread_uuid, strlen(body), body, CRLF);
            free(body_);
            break;
        }
    }
    super_free(2, name_, description);
    return cmd;
}

void cmd_create(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_create_command(command, client);
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
    char *uuid = get_arg(second_recv, 0);
    switch (client->context.type) {
        case BASE: {
            team_content_t *team = team_parse_line(second_recv, 0);
            client_print_team_created(uuid, team->name, team->description);
            team_content_free(team);
            break;
        }
        case TEAM: {
            channel_content_t *channel = channel_parse_line(second_recv, 0);
            client_print_channel_created(uuid, channel->name, channel->description);
            channel_content_free(channel);
            break;
        }
        case CHANNEL: {
            thread_content_t *thread = thread_parse_line(second_recv, 0);
            client_print_thread_created(thread->thread_uuid, thread->user_uuid, thread->timestamp, thread->title, thread->description);
            thread_content_free(thread);
            break;
        }
        case THREAD: {
            char *user_uuid = get_arg(second_recv, 1);
            char *timestamp = get_arg(second_recv, 2);
            char *reply_len = get_arg(second_recv, 3);
            char *reply = read_bytes_starting_arg(second_recv, 4, atoi(reply_len));
            client_print_reply_created(uuid, user_uuid, atoi(timestamp), reply);
            super_free(4, user_uuid, timestamp, reply_len, reply);
            break;
        }
    }
    free(uuid);
    free(real_cmd);
}
