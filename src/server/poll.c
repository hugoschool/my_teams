/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** handler.c
*/

#include "logging_server.h"
#include "server/commands.h"
#include "server/server.h"
#include "server/status.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
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
    clients_adder(server->clients, cfdr);
    WRITE_STATUS(*cfdr, 25120);
}

void client_quit(server_t *server)
{
    int fd = *CLIENT->fd;

    if (fd != server->control_fd && fd != server->signal_fd) {
        server_event_user_logged_out(CLIENT->user->uuid);
        CLIENT->user->status = false;
        if (close(fd) == -1)
            perror("close");
        poller_fd_delete(server->poller, server->index);
        clients_delete(server->clients, server->index);
        server->index--;
    }
}

void client_handler(server_t *server)
{
    size_t read_i = 0;
    int fd = server->poller->fds[server->index].fd;
    ssize_t bytes_read = 0;
    char buffer[BUFFER_SIZE + 1];

    while (true) {
        memset(buffer, 0, BUFFER_SIZE + 1);
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0 && read_i == 0)
            return client_quit(server);
        buffer[bytes_read] = 0;
        if (bytes_read < BUFFER_SIZE)
            break;
        read_i++;
    }
    server->buffer = buffer;
    commands_handler(server);
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
    for (server->index = 0;
        server->index < server->poller->amount;
        server->index++) {
        if (server->poller->fds[server->index].revents & POLLIN) {
            handle_pollin_events(server, running);
        }
    }
}
