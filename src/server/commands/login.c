/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** login.c
*/

#include "logging_server.h"
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
        dprintf(*CLIENT_I(i)->fd, "CLIENT_JOINED %s %s"CRLF,
            user->uuid, user->username);
    }
}

// TODO: not respecting protocol here, not sending:
// USERNAME uuid status
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
    user = users_add(server->users, username);
    if (user == NULL)
        return;
    client_set_user(CLIENT, user);
    server_event_user_logged_in(user->uuid);
    send_client_joined_message(server, user);
    free(username);
}
