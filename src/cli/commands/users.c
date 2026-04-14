#include "client/client.h"
#include "client/commands.h"
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

    char *real_cmd = craft_command(command, false);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BIG_BUFFER_SIZE);
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    char *second_recv = strtok(client->buffer, "\n");
    second_recv = strtok(NULL, "\n");
    while (second_recv != NULL) {
        char *uuid = get_arg(second_recv, 1);
        char *username = get_arg(second_recv, 0);
        char *status = get_arg(second_recv, 2);
        client_print_users(uuid, username, atoi(status));
        second_recv = strtok(NULL, "\n");
        free(uuid);
        free(username);
        free(status);
    }
    free(real_cmd);
}
