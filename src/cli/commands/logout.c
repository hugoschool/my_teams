#include "client/client.h"
#include "common.h"
#include "logging_client.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

void cmd_logout(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_command(command);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    recv(client->socket_fd, client->buffer, BIG_BUFFER_SIZE, 0);
    printf("%s", client->buffer);
    client->logged = false;
    free(real_cmd);
}
