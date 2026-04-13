#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_subscribe_command(char *command)
{
    char *cmd = NULL;
    char arg[UUID_STR_LEN] = {0};

    strncpy(arg, get_arg_quote(command, 1), UUID_STR_LEN);
    if (arg[strlen(arg) - 1] == '\n')
        arg[strlen(arg) - 1] = '\0';
    asprintf(&cmd, "%s %s%s", SUBSCRIBE_TEAM, arg, CRLF);
    return cmd;
}

static void subscribe_to_team(client_t *client, char *team_uuid)
{
    client->subscribed_teams ->team_uuid = realloc(client->subscribed_teams->team_uuid, sizeof(char *) * (client->subscribed_teams->amount + 1));
    client->subscribed_teams->team_uuid[client->subscribed_teams->team_index] = strdup(team_uuid);
    client->subscribed_teams->team_uuid[client->subscribed_teams->team_index + 1] = NULL;
    client->subscribed_teams->team_index += 1;
    client->subscribed_teams->amount += 1;
}

void cmd_subscribe(char *command, client_t *client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_subscribe_command(command);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    recv(client->socket_fd, client->buffer, BIG_BUFFER_SIZE, 0);
    if (strncmp(client->buffer, GET_STATUS(461), 3) == 0) {
        client_error_unknown_team(get_arg_quote(command, 1));
        return;
    }
    if (strncmp(client->buffer, GET_STATUS(450), 3) == 0) {
        printf("%s", client->buffer);
        return;
    }
    subscribe_to_team(client, get_arg_quote(command, 1));
    client_print_subscribed(client->uuid, get_arg_quote(command, 1));
    free(real_cmd);
}
