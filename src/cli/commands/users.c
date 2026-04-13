#include "client/client.h"
#include "common.h"
#include "logging_client.h"
#include "utils.h"
#include <stdlib.h>

void cmd_users(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_command(command);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    recv(client->socket_fd, client->buffer, BIG_BUFFER_SIZE, 0);
    char *second_recv = strtok(client->buffer, "\n");
    second_recv = strtok(NULL, "\n");
    while (second_recv != NULL) {
        client_print_users(get_arg(second_recv, 1), get_arg(second_recv, 0), atoi(get_arg(second_recv, 2)));
        second_recv = strtok(NULL, "\n");
    }
    free(real_cmd);
}
