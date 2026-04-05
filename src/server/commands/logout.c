/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** login.c
*/

#include "server/events.h"
#include "server/server.h"
#include "server/status.h"
#include <stdio.h>

// TODO: need to generalize this
static void send_client_left_message(server_t *server, user_data_t *user)
{
    for (unsigned int i = INITIAL_AMOUNT; i < server->clients->amount; i++) {
        if (i == server->index || CLIENT_I(i)->login_step == LOGGED_OUT)
            continue;
        dprintf(*CLIENT_I(i)->fd, CLIENT_LEFT" %s %s"CRLF,
            user->uuid, user->username);
    }
}

// Client status is handled by client_quit function
// The logging is also handled by client_quit
void command_logout(server_t *server)
{
    user_data_t *user = CLIENT->user;

    WRITE_STATUS(*CLIENT->fd, 251);
    send_client_left_message(server, user);
    client_quit(server);
}
