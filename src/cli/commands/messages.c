#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static void print_messages(client_t *client)
{
    char temp[strlen(client->buffer) + 1] = {};

    memset(temp, 0, strlen(client->buffer) + 1);
    strncpy(temp, client->buffer, strlen(client->buffer));
    char *token = strtok(temp, "\n");
    // token = strtok(temp, "\n");

    while (token != NULL) {
        if (token)
            client_private_message_print_messages(get_arg(token, 0), atoi(get_arg(token, 1)), read_bytes_starting_arg(token, 3, atoi(get_arg(token, 2))));
        token = strtok(NULL, "\n");
    }
}

void cmd_messages(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_command(command, true);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BUFFER_SIZE);
    if (strncmp(client->buffer, GET_STATUS(464), 3) == 0) {
        client_error_unknown_user(get_arg(command, 1));
        return;
    }
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    print_messages(client);
    free(real_cmd);
}
