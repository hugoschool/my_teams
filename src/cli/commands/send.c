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
    char *msg = get_arg_quote(command, 2);

    asprintf(&cmd, "%s %s %lu %s%s", SEND, get_arg_quote(command, 1), strlen(msg), msg, CRLF);
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
    recv(client->socket_fd, client->buffer, BUFFER_SIZE, 0);
    printf("%s", client->buffer);
    if (strncmp(client->buffer, GET_STATUS(460), 3) == 0) {
        client_error_unknown_user(get_arg_quote(command, 1));
        return;
    }
    free(real_cmd);
}
