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
    char *uuid = get_arg_quote(command, 1);

    strncpy(arg, uuid, UUID_STR_LEN);
    if (arg[strlen(arg) - 1] == '\n')
        arg[strlen(arg) - 1] = '\0';
    asprintf(&cmd, "%s %s%s", SUBSCRIBE_TEAM, arg, CRLF);
    free(uuid);
    return cmd;
}

void cmd_subscribe(char *command, client_t *client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_subscribe_command(command);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BIG_BUFFER_SIZE);
    remove_crlf(real_cmd);
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    char *team_uuid = get_arg(real_cmd, 1);
    client_print_subscribed(client->uuid, team_uuid);
    super_free(2, team_uuid, real_cmd);
}
