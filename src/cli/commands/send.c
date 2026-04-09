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
    char *cmd = calloc(strlen(SEND) + strlen(command), sizeof(char));

    cmd = strcat(cmd, SEND);
    cmd = strcat(cmd, " ");
    cmd = strcat(cmd, get_arg(command, 1));
    cmd = strcat(cmd, " ");
    cmd = strcat(cmd, get_arg(command, 2));
    cmd[strlen(cmd) - 1] = '\r';
    cmd = strcat(cmd, "\n");
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
        client_error_unknown_user(get_arg(command, 1));
        return;
    }
    client_event_private_message_received(get_arg(real_cmd, 1), get_arg(real_cmd, 2));
    free(real_cmd);
}
