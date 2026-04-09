#include "client/client.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>


// TODO
// Pour l'instant, cette fonction est un copié collé de /users
// Il y a besoin du user_name lié au user_uuid et le status
void cmd_user(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }

    char *real_cmd = craft_command(command);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    recv(client->socket_fd, client->buffer, BUFFER_SIZE, 0);
    if (strncmp(client->buffer, GET_STATUS(460), 3) == 0) {
        client_error_unknown_user(get_arg(command, 1));
        return;
    }
    char *second_recv = strtok(client->buffer, "\n");
    second_recv = strtok(NULL, "\n");
    client_print_user(get_arg(command, 1), get_arg(second_recv, 0), atoi(get_arg(second_recv, 2)));
    free(real_cmd);
}
