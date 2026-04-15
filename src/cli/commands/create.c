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
            char *team_name_len = get_arg(second_recv, 1);
            char *team_desc_len = get_arg(second_recv, 2);
            char *team_name = read_bytes_starting_arg(second_recv, 3, atoi(team_name_len));
            char *team_desc = read_bytes_starting_arg(second_recv, 3, atoi(team_name_len) + 1 + atoi(team_desc_len));
            client_print_team_created(uuid, team_name, team_desc + atoi(team_name_len) + 1);
            super_free(4, team_name_len, team_desc_len, team_name, team_desc);
            break;
        }
        case TEAM: {
            char *channel_name_len = get_arg(second_recv, 1);
            char *channel_desc_len = get_arg(second_recv, 2);
            char *channel_name = read_bytes_starting_arg(second_recv, 3, atoi(channel_name_len));
            char *channel_desc = read_bytes_starting_arg(second_recv, 3, atoi(channel_name_len) + 1 + atoi(channel_desc_len));
            client_print_channel_created(uuid, channel_name, channel_desc + atoi(channel_name_len) + 1);
            super_free(4, channel_name_len, channel_desc_len, channel_name, channel_desc);
            break;
        }
        case CHANNEL: {
            char *user_uuid = get_arg(second_recv, 1);
            char *timestamp = get_arg(second_recv, 2);
            char *thread_title_len = get_arg(second_recv, 3);
            char *thread_desc_len = get_arg(second_recv, 4);
            char *thread_title = read_bytes_starting_arg(second_recv, 5, atoi(thread_title_len));
            char *thread_desc = read_bytes_starting_arg(second_recv, 5, atoi(thread_title_len) + 1 + atoi(thread_desc_len));
            client_print_thread_created(uuid, user_uuid, atoi(timestamp), thread_title, thread_desc + atoi(thread_title_len) + 1);
            super_free(6, user_uuid, timestamp, thread_title_len, thread_desc_len, thread_title, thread_desc);
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
