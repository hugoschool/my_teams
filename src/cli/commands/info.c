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
    enum context_e context = define_context(client);
    switch (context) {
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
    recv(client->socket_fd, client->buffer, BUFFER_SIZE, 0);
    char *second_recv = strtok(client->buffer, "\n");
    second_recv = strtok(NULL, "\n");
    switch (context) {
        case BASE:
            client_print_user(get_arg(second_recv, 1), get_arg(second_recv, 0), atoi(get_arg(second_recv, 2)));
            break;
        case TEAM:
            client_print_team(get_arg(second_recv, 0), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1))), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 2))));
            break;
        case CHANNEL:
            client_print_channel(get_arg(second_recv, 0), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1))), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 2))));
            break;
        case THREAD:
            client_print_thread(get_arg(second_recv, 0), get_arg(second_recv, 1), atoi(get_arg(second_recv, 2)), read_bytes_starting_arg(second_recv, 5, atoi(get_arg(second_recv, 3))), read_bytes_starting_arg(second_recv, 6, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 4))));
            break;
    }
    free(real_cmd);
}
