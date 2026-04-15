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

    char *saveptr;
    char *token = strtok_r(temp, "\n", &saveptr);

    while (token != NULL) {
        if (token) {
            char *sender_uuid = get_arg(token, 0);
            char *timestamp = get_arg(token, 1);
            char *body_len = get_arg(token, 2);
            char *body = read_bytes_starting_arg(token, 3, atoi(body_len));
            client_private_message_print_messages(sender_uuid, atoi(timestamp), body);
            super_free(4, sender_uuid, timestamp, body_len, body);
        }
        token = strtok_r(NULL, "\n", &saveptr);
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
        char *uuid = get_arg(real_cmd, 1);
        client_error_unknown_user(uuid);
        free(uuid);
        return;
    }
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    print_messages(client);
    free(real_cmd);
}
