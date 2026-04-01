/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** handler.c
*/

#include "server/commands.h"
#include "server/server.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <sys/signalfd.h>
#include <sys/socket.h>
#include <unistd.h>

void new_client_handler(server_t *server)
{
    struct sockaddr_in caddr;
    socklen_t caddrl = sizeof(caddr);
    int cfd = accept(server->control_fd, (struct sockaddr *) &caddr, &caddrl);
    int *cfdr = NULL;

    if (cfd == -1) {
        perror("accept");
        return;
    }
    poller_fd_add(server->poller, cfd);
    cfdr = &server->poller->fds[server->poller->amount - 1].fd;
}

void client_quit(server_t *server)
{
}

void client_handler(server_t *server)
{
}

// server is ignored for now but will be useful later
// especially for the database
void signal_fd_handler(server_t *server, bool *running)
{
    (void)server;
    *running = false;
}

static void handle_pollin_events(server_t *server, bool *running)
{
    if (server->poller->fds[server->index].fd == server->control_fd)
        new_client_handler(server);
    else if (server->poller->fds[server->index].fd == server->signal_fd)
        signal_fd_handler(server, running);
    else
        client_handler(server);
}

void poll_handler(server_t *server, bool *running)
{
    unsigned int amount = server->poller->amount;

    for (server->index = 0; server->index < amount; server->index++) {
        if (server->poller->fds[server->index].revents & POLLIN) {
            handle_pollin_events(server, running);
        }
    }
}
