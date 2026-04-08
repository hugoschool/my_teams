/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** messages.c
*/

#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: generalize this
static user_data_t *get_user(server_t *server)
{
    user_data_t *user = NULL;
    char *uuid = get_arg(server->buffer, 1);

    user = users_get_from_uuid(server->users, uuid);
    free(uuid);
    return user;
}

void command_messages(server_t *server)
{
    user_data_t *user = NULL;
    message_data_t *message = NULL;

    user = get_user(server);
    if (user == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    for (unsigned int i = 0; i < server->messages->amount; i++) {
        message = MESSAGE_I(i);
        if ((strcmp(CLIENT->user->uuid, message->user_uuid_from) == 0
            && strcmp(user->uuid, message->user_uuid_to) == 0) ||
            (strcmp(CLIENT->user->uuid, message->user_uuid_to) == 0
            && strcmp(user->uuid, message->user_uuid_from) == 0))
            dprintf(*CLIENT->fd, "%s %ld %ld %s\n", message->user_uuid_from,
                message->timestamp, strlen(message->body), message->body);
    }
}
