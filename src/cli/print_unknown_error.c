#include "client/client.h"
#include "client/commands.h"
#include "logging_client.h"
#include "server/status.h"

bool print_unknown_error(client_t *client)
{
    if (strncmp(client->buffer, GET_STATUS(461), 3) == 0) {
        client_error_unknown_team(client->context.team_uuid);
        return true;
    }
    if (strncmp(client->buffer, GET_STATUS(462), 3) == 0) {
        client_error_unknown_channel(client->context.channel_uuid);
        return true;
    }
    if (strncmp(client->buffer, GET_STATUS(463), 3) == 0) {
        client_error_unknown_thread(client->context.thread_uuid);
        return true;
    }
    return false;
}
