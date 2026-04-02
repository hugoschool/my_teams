/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** login.c
*/

#include "server/server.h"
#include "server/status.h"

// TODO: send a message to all other clients about login
void command_login(server_t *server)
{
    if (CLIENT->login_step == LOGGED_IN) {
        WRITE_STATUS(*CLIENT->fd, 430);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 250);
    CLIENT->login_step = LOGGED_IN;
    // TODO: actually login and create a user
    return;
}
