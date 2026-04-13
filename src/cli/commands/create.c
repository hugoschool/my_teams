#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_create_command(char *command, const char *context, client_t *client)
{
    char *cmd = NULL;
    char name[MAX_NAME_LENGTH] = {0};
    char desc[MAX_DESCRIPTION_LENGTH] = {0};

    if (command[strlen(command) - 1] == '\n')
        command[strlen(command) - 1] = '\0';
    if (strcmp(context, CREATE_COMMENT) == 0) {
        char body[MAX_BODY_LENGTH] = {0};
        strncpy(body, get_arg_quote(command, 1), MAX_BODY_LENGTH);
        asprintf(&cmd, "%s %s %s %s %lu %s%s", context, client->context.team_uuid, client->context.channel_uuid, client->context.thread_uuid, strlen(body), body, CRLF);
    } else if (strcmp(context, CREATE_TEAM) == 0) {
        strncpy(name, get_arg_quote(command, 1), MAX_NAME_LENGTH);
        strncpy(desc, get_arg_quote(command, 2), MAX_DESCRIPTION_LENGTH);
        asprintf(&cmd, "%s %lu %lu %s %s%s", context, strlen(name), strlen(desc), name, desc, CRLF);
    } else if (strcmp(context, CREATE_CHANNEL) == 0) {
        strncpy(name, get_arg_quote(command, 1), MAX_NAME_LENGTH);
        strncpy(desc, get_arg_quote(command, 2), MAX_DESCRIPTION_LENGTH);
        asprintf(&cmd, "%s %s %lu %lu %s %s%s", context, client->context.team_uuid, strlen(name), strlen(desc), name, desc, CRLF);
    } else if (strcmp(context, CREATE_THREAD) == 0) {
        strncpy(name, get_arg_quote(command, 1), MAX_NAME_LENGTH);
        strncpy(desc, get_arg_quote(command, 2), MAX_DESCRIPTION_LENGTH);
        asprintf(&cmd, "%s %s %s %lu %lu %s %s%s", context, client->context.team_uuid, client->context.channel_uuid, strlen(name), strlen(desc), name, desc, CRLF);
    }
    return cmd;
}

enum context_e define_context(client_t *client)
{
    if (strcmp(client->context.team_uuid, "\0") == 0 && strcmp(client->context.team_uuid, "\0") == 0 && strcmp(client->context.team_uuid, "\0") == 0)
        return BASE;
    if (strcmp(client->context.team_uuid, "\0") != 0 && strcmp(client->context.team_uuid, "\0") == 0 && strcmp(client->context.team_uuid, "\0") == 0) {
        return TEAM;
    }
    if (strcmp(client->context.team_uuid, "\0") != 0 && strcmp(client->context.team_uuid, "\0") != 0 && strcmp(client->context.team_uuid, "\0") == 0)
        return CHANNEL;
    return THREAD;
}

void cmd_create(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = NULL;
    enum context_e context = define_context(client);
    switch (context) {
        case BASE:
            real_cmd = craft_create_command(command, CREATE_TEAM, client);
            break;
        case TEAM:
            real_cmd = craft_create_command(command, CREATE_CHANNEL, client);
            break;
        case CHANNEL:
            real_cmd = craft_create_command(command, CREATE_THREAD, client);
            break;
        case THREAD:
            real_cmd = craft_create_command(command, CREATE_COMMENT, client);
            break;
    }
    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    recv(client->socket_fd, client->buffer, BIG_BUFFER_SIZE, 0);
    if (strncmp(client->buffer, GET_STATUS(440), 3) == 0) {
        client_error_already_exist();
        free(real_cmd);
        return;
    }
    if (print_unknown_error(client)) {
        free(real_cmd);
        return;
    }
    char *second_recv = strtok(client->buffer, "\n");
    second_recv = strtok(NULL, "\n");
    switch (context) {
        case BASE:
            client_print_team_created(get_arg(second_recv, 0), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1))), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 2))));
            break;
        case TEAM:
            client_print_channel_created(get_arg(second_recv, 0), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1))), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 2))));
            break;
        case CHANNEL:
            client_print_thread_created(get_arg(second_recv, 0), get_arg(second_recv, 1), atoi(get_arg(second_recv, 2)), read_bytes_starting_arg(second_recv, 5, atoi(get_arg(second_recv, 3))), read_bytes_starting_arg(second_recv, 6, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 4))));
            break;
        case THREAD:
            client_print_reply_created(get_arg(second_recv, 0), get_arg(second_recv, 1), atoi(get_arg(second_recv, 2)), read_bytes_starting_arg(second_recv, 4, atoi(get_arg(second_recv, 3))));
            break;
    }
    free(real_cmd);
}
