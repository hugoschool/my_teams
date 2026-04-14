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
    if (strncmp(client->buffer, GET_STATUS(464), 3) == 0) {
        client_error_unknown_user(get_arg_quote(command, 1));
        return;
    }
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    char *second_recv = strtok(client->buffer, "\n");
    second_recv = strtok(NULL, "\n");
    client_print_user(get_arg_quote(command, 1), get_arg(second_recv, 0), atoi(get_arg(second_recv, 2)));
    free(real_cmd);
}
