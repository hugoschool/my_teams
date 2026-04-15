#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static char *craft_send_command(char *command)
{
    char *cmd = NULL;
    char arg[UUID_STR_LEN] = {0};
    char msg[MAX_BODY_LENGTH] = {0};
    char *uuid = get_arg_quote(command, 1);
    char *message = get_arg_quote(command, 3);

    strncpy(arg, uuid, UUID_STR_LEN);
    strncpy(msg, message, MAX_BODY_LENGTH);
    asprintf(&cmd, "%s %s %lu %s%s", SEND, arg, strlen(msg), msg, CRLF);
    super_free(2, uuid, message);
    return cmd;
}

void cmd_send(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_send_command(command);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BIG_BUFFER_SIZE);
    if (strncmp(client->buffer, GET_STATUS(464), 3) == 0) {
        char *uuid = get_arg(real_cmd, 1);
        client_error_unknown_user(uuid);
        free(uuid);
        return;
    }
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    free(real_cmd);
}
