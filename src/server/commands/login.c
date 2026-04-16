/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** login.c
*/

#include "logging_server.h"
#include "server/commands.h"
#include "server/events.h"
#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static void send_client_joined_message(server_t *server, user_data_t *user)
{
    for (unsigned int i = INITIAL_AMOUNT; i < server->clients->amount; i++) {
        if (i == server->index || CLIENT_I(i)->login_step == LOGGED_OUT)
            continue;
        dprintf(*CLIENT_I(i)->fd, CLIENT_JOINED" %s %s"CRLF,
            user->uuid, user->username);
    }
}

static user_data_t *get_user(users_t *users, char *username)
{
    user_data_t *user = NULL;

    user = users_get_from_username(users, username);
    if (user == NULL) {
        user = users_add(users, username);
        server_event_user_created(user->uuid, user->username);
    } else
        server_event_user_loaded(user->uuid, user->username);
    return user;
}

void command_login(server_t *server)
{
    char *username = NULL;
    user_data_t *user = NULL;

    if (CLIENT->login_step == LOGGED_IN) {
        WRITE_STATUS(*CLIENT->fd, 430);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 250);
    CLIENT->login_step = LOGGED_IN;
    username = get_arg(server->buffer, 1);
    if (username == NULL)
        return;
    user = get_user(server->users, username);
    free(username);
    if (user == NULL) {
        WRITE_STATUS(*CLIENT->fd, 499);
        return;
    }
    user->status = true;
    client_set_user(CLIENT, user);
    server_event_user_logged_in(user->uuid);
    send_client_joined_message(server, user);
    user_print(*CLIENT->fd, user);
}
