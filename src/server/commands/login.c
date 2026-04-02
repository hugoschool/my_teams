/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** login.c
*/

#include "logging_server.h"
#include "server/server.h"
#include "server/status.h"
#include <stdio.h>

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
    char *username = "yo";
    user_data_t *user = NULL;

    if (CLIENT->login_step == LOGGED_IN) {
        WRITE_STATUS(*CLIENT->fd, 430);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 250);
    CLIENT->login_step = LOGGED_IN;
    // TODO: get parameter
    user = users_add(server->users, username);
    if (user == NULL)
        return;
    server_event_user_logged_in(user->uuid);
    send_client_joined_message(server, user);
    return;
}
