/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** server.c
*/

#include "server/args.h"
#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>

static server_t *server_init(void)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL) {
        perror("malloc");
        return NULL;
    }
    server->poller = poller_init();
    if (server->poller == NULL) {
        free(server);
        return NULL;
    }
    server->control_fd = -1;
    return server;
}

void server_free(server_t *server)
{
    if (server == NULL)
        return;
    if (server->poller)
        poller_free(server->poller);
    free(server);
}

static void server_loop(server_t *server)
{
    while (true) {}
}

bool teams_server(args_t *args)
{
    server_t *server = server_init();

    if (server == NULL)
        return false;
    server->control_fd = socket_init(args->port);
    if (server->control_fd == -1) {
        server_free(server);
        return false;
    }
    poller_set_init_socket(server->poller, server->control_fd);
    server_loop(server);
    server_free(server);
    return true;
}
