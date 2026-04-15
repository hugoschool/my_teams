#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "utils.h"
#include <stdlib.h>

void cmd_user(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_command(command, true);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BIG_BUFFER_SIZE);
    char *user = get_arg(real_cmd, 1);
    if (strncmp(client->buffer, GET_STATUS(464), 3) == 0) {
        client_error_unknown_user(user);
        free(user);
        free(real_cmd);
        return;
    }
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    char *saveptr;
    char *second_recv = strtok_r(client->buffer, "\n", &saveptr);
    second_recv = strtok_r(NULL, "\n", &saveptr);
    char *username = get_arg(second_recv, 0);
    char *status = get_arg(second_recv, 2);
    client_print_user(user, username, atoi(status));
    super_free(4, user, username, status, real_cmd);
}
