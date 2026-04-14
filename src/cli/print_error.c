#include "client/client.h"
#include "client/commands.h"
#include "logging_client.h"
#include "server/status.h"
#include <stdio.h>

bool print_error(client_t *client)
{
    if (strncmp(client->buffer, GET_STATUS(430), 3) == 0) {
        dprintf(STDOUT_FILENO, "Client is already logged in.\n");
        return true;
    }
    if (strncmp(client->buffer, GET_STATUS(435), 3) == 0) {
        client_error_unauthorized();
        return true;
    }
    if (strncmp(client->buffer, GET_STATUS(440), 3) == 0) {
        client_error_already_exist();
        return true;
    }
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
    if (strncmp(client->buffer, GET_STATUS(450), 3) == 0) {
        dprintf(STDOUT_FILENO, "Already subscribed to this team.\n");
        return true;
    }
    if (strncmp(client->buffer, GET_STATUS(451), 3) == 0) {
        dprintf(STDOUT_FILENO, "Not subscribed to this team.\n");
        return true;
    }
    if (strncmp(client->buffer, GET_STATUS(460), 3) == 0) {
        dprintf(STDOUT_FILENO, "Invalid parameters.\n");
        return true;
    }
    if (strncmp(client->buffer, GET_STATUS(499), 3) == 0) {
        dprintf(STDOUT_FILENO, "Badly formed request.\n");
        return true;
    }
    return false;
}
