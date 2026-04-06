#include "client/client.h"
#include "common.h"
#include "logging_client.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

char *craft_command(char *command)
{
    char *cmd = malloc(sizeof(strlen(command)) + 3);

    cmd = strcat(cmd, capitalize_cmd(command));
    cmd[strlen(cmd) - 1] = '\0';
    cmd = strcat(cmd, CRLF);
    return cmd;
}

void cmd_login(char *command, client_t * client)
{
    printf("%s", craft_command(command));
    send(client->socket_fd, craft_command(command), 4096, 0);
    recv(client->socket_fd, client->buffer, 4096, 0);
    printf("%s", client->buffer);
    client_event_logged_in("doug", get_arg(command, 1));
}
