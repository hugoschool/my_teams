#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "server/status.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>

static void release_context(client_t *client)
{
    memset(client->context.channel_uuid, '\0', UUID_STR_LEN);
    memset(client->context.team_uuid, '\0', UUID_STR_LEN);
    memset(client->context.thread_uuid, '\0', UUID_STR_LEN);
}

static bool verify_arg(char *command, client_t *client, const char *info, int nbarg, const char *err)
{
    char *cmd = NULL;
    char *arg = get_arg_quote(command, nbarg);

    if (arg[strlen(arg) - 1] == '\n')
        arg[strlen(arg) - 1] = '\0';
    asprintf(&cmd, "%s %s%s", info, arg, CRLF);
    send(client->socket_fd, cmd, strlen(cmd), 0);
    recv(client->socket_fd, client->buffer, BUFFER_SIZE, 0);
    free(cmd);
    if (strncmp(client->buffer, GET_STATUS(460), 3) == 0) {
        memset(client->buffer, '\0', BUFFER_SIZE);
        printf("Invalid %s\n", err);
        return false;
    }
    memset(client->buffer, '\0', BUFFER_SIZE);
    return true;
}

void cmd_use(char *command, client_t * client)
{
    if (!client->logged) {
        client_error_unauthorized();
        return;
    }
    switch (arg_amount_quote(command)) {
        case 0:
            release_context(client);
            break;
        case 1:
            if (!verify_arg(command, client, TEAM_INFO, 1, "team"))
                return;
            strcpy(client->context.team_uuid, get_arg_quote(command, 1));
            memset(client->context.channel_uuid, '\0', UUID_STR_LEN);
            memset(client->context.thread_uuid, '\0', UUID_STR_LEN);
            break;
        case 2:
            if (verify_arg(command, client, TEAM_INFO, 1, "team") || !verify_arg(command, client, CHANNEL_INFO, 2, "channel"))
                return;
            strcpy(client->context.team_uuid, get_arg_quote(command, 1));
            strcpy(client->context.channel_uuid, get_arg_quote(command, 2));
            memset(client->context.thread_uuid, '\0', UUID_STR_LEN);
            break;
        case 3:
            if (verify_arg(command, client, TEAM_INFO, 1, "team") || !verify_arg(command, client, CHANNEL_INFO, 2, "channel") || !verify_arg(command, client, THREAD_INFO, 3, "thread"))
                return;
            strcpy(client->context.team_uuid, get_arg_quote(command, 1));
            strcpy(client->context.channel_uuid, get_arg_quote(command, 2));
            strcpy(client->context.thread_uuid, get_arg_quote(command, 3));
            break;
    }
}
