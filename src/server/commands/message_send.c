/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** user.c
*/

#include "logging_server.h"
#include "server/commands.h"
#include "server/events.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static user_data_t *get_user(server_t *server)
{
    user_data_t *user = NULL;
    char *uuid = get_arg(server->buffer, 1);

    user = users_get_from_uuid(server->users, uuid);
    free(uuid);
    return user;
}

static void send_to_other_user(server_t *server, message_data_t *message)
{
    for (unsigned int i = INITIAL_AMOUNT; i < server->clients->amount; i++) {
        if (strcmp(CLIENT_I(i)->user->uuid, message->user_uuid_to) == 0) {
            dprintf(*CLIENT_I(i)->fd, NEW_MESSAGE" %s %s"CRLF,
                message->user_uuid_from, message->body);
        }
    }
}

void command_message_send(server_t *server)
{
    user_data_t *user = NULL;
    char *text_uuid = NULL;
    text_data_t *text = NULL;
    message_data_t *message = NULL;

    user = get_user(server);
    if (user == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    text_uuid = get_arg(server->buffer, 2);
    if (text_uuid == NULL)
        return;
    text = texts_consume(server->texts, text_uuid);
    if (text == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    free(text_uuid);
    message = messages_add(server->messages, CLIENT->user->uuid,
        user->uuid, text->body);
    text_data_free(text);
    if (message == NULL)
        return;
    WRITE_STATUS(*CLIENT->fd, 200);
    send_to_other_user(server, message);
    server_event_private_message_sended(message->user_uuid_from,
        message->user_uuid_to, message->body);
}
