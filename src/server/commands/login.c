/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** login.c
*/

#include "server/server.h"
#include "server/status.h"

// TODO: send a message to all other clients about login
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
    // TODO: log with logging library
    return;
}
