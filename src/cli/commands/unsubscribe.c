#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_unsubscribe_command(char *command)
{
    char *cmd = NULL;
    char arg[UUID_STR_LEN] = {0};
    char *uuid = get_arg_quote(command, 1);

    strncpy(arg, uuid, UUID_STR_LEN);
    if (arg[strlen(arg) - 1] == '\n')
        arg[strlen(arg) - 1] = '\0';
    asprintf(&cmd, "%s %s%s", UNSUBSCRIBE_TEAM, arg, CRLF);
    free(uuid);
    return cmd;
}

static void unsubscribe_of_team(client_t *client, char *team_uuid)
{
    bool deleted = false;
    for (int i = 0; client->subscribed_teams->team_uuid[i] != NULL; i++) {
        if (strcmp(client->subscribed_teams->team_uuid[i], team_uuid) == 0) {
            free(client->subscribed_teams->team_uuid[i]);
            client->subscribed_teams->team_uuid[i] = NULL;
            deleted = true;
            continue;
        }
        if (deleted) {
            if (client->subscribed_teams->team_uuid[i]) {
                client->subscribed_teams->team_uuid[i - 1] = strdup(client->subscribed_teams->team_uuid[i]);
            }
        }
    }
    client->subscribed_teams->amount -= 1;
    client->subscribed_teams->team_index -= 1;
    client->subscribed_teams->team_uuid[client->subscribed_teams->team_index + 1] = NULL;
}

void cmd_unsubscribe(char *command, client_t *client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_unsubscribe_command(command);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BIG_BUFFER_SIZE);
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    char *team_uuid = get_arg_quote(real_cmd, 1);
    unsubscribe_of_team(client, team_uuid);
    client_print_unsubscribed(client->uuid, team_uuid);
    free(team_uuid);
    free(real_cmd);
}
