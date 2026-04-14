#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_subscribed_command(char *command)
{
    char *cmd = NULL;
    char *arg = get_arg_quote(command, 1);

    if (arg[strlen(arg) - 1] == '\n')
        arg[strlen(arg) - 1] = '\0';
    asprintf(&cmd, "%s %s%s", SUBSCRIBED_LIST, arg, CRLF);
    return cmd;
}

void cmd_subscribed(char *command, client_t *client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = NULL;

    if (arg_amount_quote(command) == 1) {
        real_cmd = capitalize_cmd(command);
        send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
        receive(client, BIG_BUFFER_SIZE);
        char *second_recv = strtok(client->buffer, "\n");
        second_recv = strtok(NULL, "\n");
        while (second_recv != NULL) {
            client_print_teams(get_arg(second_recv, 0), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1))), read_bytes_starting_arg(second_recv, 3, atoi(get_arg(second_recv, 1)) + 1 + atoi(get_arg(second_recv, 2))));
            second_recv = strtok(NULL, "\n");
        }
    } else {
        real_cmd = craft_subscribed_command(command);
        send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
        receive(client, BIG_BUFFER_SIZE);
        if (strncmp(client->buffer, GET_STATUS(461), 3) == 0) {
            client_error_unknown_team(get_arg_quote(command, 1));
            return;
        }
        char *second_recv = strtok(client->buffer, "\n");
        second_recv = strtok(NULL, "\n");
        while (second_recv != NULL) {
            client_print_users(get_arg(second_recv, 1), get_arg(second_recv, 0), atoi(get_arg(second_recv, 2)));
            second_recv = strtok(NULL, "\n");
        }
    }
    free(real_cmd);
}
