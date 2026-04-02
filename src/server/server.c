/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** server.c
*/

#include "server/args.h"
#include "server/server.h"
#include <signal.h>
#include <sys/poll.h>
#include <sys/signalfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static server_t *server_init(void)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL) {
        perror("malloc");
        return NULL;
    }
    server->poller = poller_init();
    server->clients = clients_init();
    if (server->poller == NULL || server->clients == NULL) {
        free(server);
        return NULL;
    }
    server->users = NULL;
    server->teams = NULL;
    server->control_fd = -1;
    server->signal_fd = -1;
    return server;
}

void server_free(server_t *server)
{
    if (server == NULL)
        return;
    if (server->poller)
        poller_free(server->poller);
    if (server->clients)
        clients_free(server->clients);
    free(server);
}

static void server_loop(server_t *server)
{
    int result = 0;
    bool running = true;

    while (running) {
        result = poll(server->poller->fds, server->poller->amount, -1);
        if (result == -1) {
            perror("poll");
            break;
        }
        poll_handler(server, &running);
    }
}

static int handle_signal(void)
{
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
        return -1;
    return signalfd(-1, &mask, 0);
}

bool teams_server(args_t *args)
{
    server_t *server = server_init();

    if (server == NULL)
        return false;
    server->control_fd = socket_init(args->port);
    server->signal_fd = handle_signal();
    if (server->control_fd == -1 || server->signal_fd == -1) {
        server_free(server);
        return false;
    }
    poller_set_init_values(server->poller, server->control_fd,
        server->signal_fd);
    server_loop(server);
    server_free(server);
    return true;
}
