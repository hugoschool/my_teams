#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
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
    char *saveptr;
    char *second_recv = strtok_r(client->buffer, "\r\n", &saveptr);
    second_recv = strtok_r(NULL, "\n", &saveptr);
    while (second_recv != NULL) {
        char *uuid = get_arg(second_recv, 1);
        char *username = get_arg(second_recv, 0);
        char *status = get_arg(second_recv, 2);
        client_print_users(uuid, username, atoi(status));
        super_free(3, uuid, username, status);
        second_recv = strtok_r(NULL, "\n", &saveptr);
    }
}

static void subscribed_zero_arg(client_t *client)
{
    char *saveptr;
    char *second_recv = strtok_r(client->buffer, "\r\n", &saveptr);
    second_recv = strtok_r(NULL, "\n", &saveptr);
    while (second_recv != NULL) {
        team_content_t *team = team_parse_line(second_recv, 0);
        client_print_teams(team->uuid, team->name, team->description);
        team_content_free(team);
        second_recv = strtok_r(NULL, "\n", &saveptr);
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
        remove_crlf(real_cmd);
        if (print_error(client)) {
            free(real_cmd);
            return;
        }
        subscribed_one_arg(client);
    } else {
        real_cmd = craft_command(command, false);
        send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
        receive(client, BIG_BUFFER_SIZE);
        remove_crlf(real_cmd);
        if (print_error(client)) {
            free(real_cmd);
            return;
        }
        subscribed_zero_arg(client);
    }
    free(real_cmd);
}
