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
    char *arg = get_arg_quote(command, 1);

    if (arg[strlen(arg) - 1] == '\n')
        arg[strlen(arg) - 1] = '\0';
    asprintf(&cmd, "%s %s%s", UNSUBSCRIBE_TEAM, arg, CRLF);
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
                client->subscribed_teams->team_uuid[i - 1] = strcpy(client->subscribed_teams->team_uuid[i - 1], client->subscribed_teams->team_uuid[i]);
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
    recv(client->socket_fd, client->buffer, BUFFER_SIZE, 0);
    if (strncmp(client->buffer, GET_STATUS(460), 3) == 0) {
        client_error_unknown_team(get_arg_quote(command, 1));
        return;
    }
    if (strncmp(client->buffer, GET_STATUS(451), 3) == 0) {
        printf("%s", client->buffer);
        return;
    }
    unsubscribe_of_team(client, get_arg_quote(command, 1));
    client_print_unsubscribed(client->uuid, get_arg_quote(command, 1));
    free(real_cmd);
}
