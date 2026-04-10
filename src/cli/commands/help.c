#include "client/client.h"
#include "stdio.h"

void cmd_help(char *command, client_t * client)
{
    (void)command;
    (void)client;
    printf("Commands:\n"
    "/help\n"
    "/login [username]\n"
    "/logout\n"
    "/user [user_uuid]\n"
    "/users\n"
    "/send [user_uuid] [message]\n"
    "/messages [user_uuid]\n"
    "/subscribe [team_uuid]\n"
    "/subscribed [team_uuid]?\n"
    "/unsubscribe [team_uuid]\n"
    "/use [team_uuid]? [channel_uuid]? [thread_uuid]?\n"
    "/create (depends on the context)\n"
    "/list (depends on the context)\n"
    "/info (depends on the context)\n"
    );
}
