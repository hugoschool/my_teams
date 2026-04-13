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
            strcpy(client->context.team_uuid, get_arg_quote(command, 1));
            memset(client->context.channel_uuid, '\0', UUID_STR_LEN);
            memset(client->context.thread_uuid, '\0', UUID_STR_LEN);
            break;
        case 2:
            strcpy(client->context.team_uuid, get_arg_quote(command, 1));
            strcpy(client->context.channel_uuid, get_arg_quote(command, 2));
            memset(client->context.thread_uuid, '\0', UUID_STR_LEN);
            break;
        case 3:
            strcpy(client->context.team_uuid, get_arg_quote(command, 1));
            strcpy(client->context.channel_uuid, get_arg_quote(command, 2));
            strcpy(client->context.thread_uuid, get_arg_quote(command, 3));
            break;
    }
}
