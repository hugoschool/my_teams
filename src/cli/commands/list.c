#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_list_command(const char *context, client_t *client)
{
    char *cmd = NULL;

    if (strcmp(context, TEAM_LIST) == 0) {
        asprintf(&cmd, "%s%s", context, CRLF);
    } else if (strcmp(context, CHANNEL_LIST) == 0) {
        asprintf(&cmd, "%s %s%s", context, client->context.team_uuid, CRLF);
    } else if (strcmp(context, THREAD_LIST) == 0) {
        asprintf(&cmd, "%s %s %s%s", context, client->context.team_uuid, client->context.channel_uuid, CRLF);
    } else if (strcmp(context, COMMENT_LIST) == 0) {
        asprintf(&cmd, "%s %s %s %s%s", context, client->context.team_uuid, client->context.channel_uuid, client->context.thread_uuid, CRLF);
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
    char *real_cmd = NULL;
    enum context_e context = define_context(client);
    switch (context) {
        case BASE:
            real_cmd = craft_list_command(TEAM_LIST, client);
            break;
        case TEAM:
            real_cmd = craft_list_command(CHANNEL_LIST, client);
            break;
        case CHANNEL:
            real_cmd = craft_list_command(THREAD_LIST, client);
            break;
        case THREAD:
            real_cmd = craft_list_command(COMMENT_LIST, client);
            break;
    }
    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BIG_BUFFER_SIZE);
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    char *second_recv = strtok(client->buffer, "\n");
    second_recv = strtok(NULL, "\n");
    while (second_recv != NULL) {
        switch (context) {
            case BASE:
                client_print_teams(get_arg(second_recv, 0), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1))), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 2))));
                break;
            case TEAM:
                client_team_print_channels(get_arg(second_recv, 0), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1))), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 2))));
                break;
            case CHANNEL:
                client_channel_print_threads(get_arg(second_recv, 0), get_arg(second_recv, 1), atoi(get_arg(second_recv, 2)), read_bytes_starting_arg(second_recv, 5, atoi(get_arg(second_recv, 3))), read_bytes_starting_arg(second_recv, 6, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 4))));
                break;
            case THREAD:
                client_thread_print_replies(client->context.thread_uuid, get_arg(second_recv, 1), atoi(get_arg(second_recv, 2)), read_bytes_starting_arg(second_recv, 4, atoi(get_arg(second_recv, 3))));
                break;
        }
        second_recv = strtok(NULL, "\n");
    }
    free(real_cmd);
}
