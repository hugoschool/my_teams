#include "client/client.h"
#include "common.h"
#include "logging_client.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

char *craft_command(char *command)
{
    char *cmd = NULL;

    command = capitalize_cmd(command);
    if (command[strlen(command) - 1] == '\n')
        command[strlen(command) - 1] = '\0';
    asprintf(&cmd, "%s%s", command, CRLF);
    return cmd;
}

void cmd_login(char *command, client_t *client)
{
    char *real_cmd = craft_command(command);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    recv(client->socket_fd, client->buffer, BUFFER_SIZE, 0);
    printf("%s", client->buffer);
    memset(client->buffer, '\0', BUFFER_SIZE);
    recv(client->socket_fd, client->buffer, BUFFER_SIZE, 0);
    strncpy(client->user_name, get_arg_quote(command, 1), MAX_NAME_LENGTH);
    strcpy(client->uuid, get_arg(client->buffer, 1));
    client->logged = true;
    free(real_cmd);
}
