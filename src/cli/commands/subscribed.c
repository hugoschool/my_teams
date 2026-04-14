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

static void subscribed_one_arg(client_t *client)
{
    char *second_recv = strtok(client->buffer, "\r\n");
    second_recv = strtok(NULL, "\n");
    while (second_recv != NULL) {
        char *uuid = get_arg(second_recv, 1);
        char *username = get_arg(second_recv, 0);
        char *status = get_arg(second_recv, 2);
        client_print_users(uuid, username, atoi(status));
        free(uuid);
        free(username);
        free(status);
        second_recv = strtok(NULL, "\n");
    }
}

static void subscribed_zero_arg(client_t *client)
{
    char *second_recv = strtok(client->buffer, "\r\n");
    second_recv = strtok(NULL, "\n");
    while (second_recv != NULL) {
        char *team_uuid = get_arg(second_recv, 0);
        char *team_name_len = get_arg(second_recv, 1);
        char *team_desc_len = get_arg(second_recv, 2);
        char *team_name = read_bytes_starting_arg(second_recv, 3, atoi(team_name_len));
        char *team_desc = read_bytes_starting_arg(second_recv, 3, atoi(team_name_len) + 1 + atoi(team_desc_len)) + atoi(team_name_len) + 1;
        client_print_teams(team_uuid, team_name, team_desc);
        free(team_uuid);
        free(team_name_len);
        free(team_desc_len);
        free(team_name);
        free(team_desc);
        second_recv = strtok(NULL, "\n");
    }
}

void cmd_subscribed(char *command, client_t *client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = NULL;

    if (arg_amount_quote(command) == 1) {
        real_cmd = craft_subscribed_command(command);
        send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
        receive(client, BIG_BUFFER_SIZE);
        if (print_error(client)) {
            free(real_cmd);
            return;
        }
        subscribed_one_arg(client);
    } else {
        real_cmd = craft_command(command, false);
        send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
        receive(client, BIG_BUFFER_SIZE);
        if (print_error(client)) {
            free(real_cmd);
            return;
        }
        subscribed_zero_arg(client);
    }
    free(real_cmd);
}
