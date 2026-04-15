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
    char *team_uuid = NULL;
    char *channel_uuid = NULL;
    char *thread_uuid = NULL;
    switch (arg_amount_quote(command)) {
        case 0:
            release_context(client);
            break;
        case 1:
            team_uuid = get_arg_quote(command, 1);
            strncpy(client->context.team_uuid, team_uuid, UUID_STR_LEN);
            memset(client->context.channel_uuid, '\0', UUID_STR_LEN);
            memset(client->context.thread_uuid, '\0', UUID_STR_LEN);
            break;
        case 2:
            team_uuid = get_arg_quote(command, 1);
            channel_uuid = get_arg_quote(command, 3);
            strncpy(client->context.team_uuid, team_uuid, UUID_STR_LEN);
            strncpy(client->context.channel_uuid, channel_uuid, UUID_STR_LEN);
            memset(client->context.thread_uuid, '\0', UUID_STR_LEN);
            break;
        case 3:
            team_uuid = get_arg_quote(command, 1);
            channel_uuid = get_arg_quote(command, 3);
            thread_uuid = get_arg_quote(command, 5);
            strncpy(client->context.team_uuid, team_uuid, UUID_STR_LEN);
            strncpy(client->context.channel_uuid, channel_uuid, UUID_STR_LEN);
            strncpy(client->context.thread_uuid, thread_uuid, UUID_STR_LEN);
            break;
    }
    super_free(3, team_uuid, channel_uuid, thread_uuid);
}
