#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

char *craft_command(char *command, bool is_arg)
{
    char *cmd = NULL;

    command = capitalize_cmd(command);
    if (command[strlen(command) - 1] == '\n')
        command[strlen(command) - 1] = '\0';
    char *arg = NULL;
    if (is_arg) {
        arg = get_arg_quote(command, 1);
    }
    if (arg) {
        char temp[strlen(command)];
        memset(temp, '\0', strlen(command));
        strncpy(temp, command, strlen(get_arg(command, 0)));
        memset(command, '\0', strlen(command));
        command = strcat(command, temp);
        command = strcat(command, " ");
        command = strcat(command, arg);
    }
    asprintf(&cmd, "%s%s", command, CRLF);
    if (arg)
        free(arg);
    return cmd;
}

void cmd_login(char *command, client_t *client)
{
    char *real_cmd = craft_command(command, true);

    send(client->socket_fd, real_cmd, strlen(real_cmd), 0);
    receive(client, BIG_BUFFER_SIZE);
    if (print_error(client)) {
        free(real_cmd);
        return;
    }
    char *second_recv = strtok(client->buffer, "\n");
    second_recv = strtok(NULL, "\n");
    strncpy(client->user_name, get_arg(real_cmd, 1), MAX_NAME_LENGTH);
    strcpy(client->uuid, get_arg(second_recv, 1));
    client->logged = true;
    client_event_logged_in(client->uuid, client->user_name);
    free(real_cmd);
}
