/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** poller.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

poller_t *poller_init(void)
{
    poller_t *poller = malloc(sizeof(poller_t));

    if (poller == NULL) {
        perror("malloc");
        exit(84);
    }
    poller->fds = calloc(POLLER_INIT_SIZE, sizeof(struct pollfd));
    if (poller->fds == NULL) {
        perror("calloc");
        exit(84);
    }
    poller->amount = INITIAL_AMOUNT;
    poller->size = POLLER_INIT_SIZE;
    return poller;
}

void poller_free(poller_t *poller)
{
    free(poller->fds);
    free(poller);
}

static void poller_set_init_socket(poller_t *poller, int socket_fd)
{
    poller->fds[0].fd = socket_fd;
    poller->fds[0].events = POLLIN;
    poller->fds[0].revents = 0;
}

static void poller_set_signal_fd(poller_t *poller, int signal_fd)
{
    poller->fds[1].fd = signal_fd;
    poller->fds[1].events = POLLIN;
    poller->fds[1].revents = 0;
}

void poller_set_init_values(poller_t *poller, int socket_fd, int signal_fd)
{
    poller_set_init_socket(poller, socket_fd);
    poller_set_signal_fd(poller, signal_fd);
}

void poller_fd_add(poller_t *poller, int fd)
{
    if (poller->amount == poller->size) {
        poller->size += 1;
        poller->fds =
            realloc(poller->fds, sizeof(struct pollfd) * (poller->size));
        if (poller->fds == NULL) {
            perror("realloc");
            exit(84);
        }
    }
    poller->fds[poller->amount].fd = fd;
    poller->fds[poller->amount].events = POLLIN;
    poller->fds[poller->amount].revents = 0;
    poller->amount++;
}

void poller_fd_delete(poller_t *poller, int i)
{
    poller->fds[i] = poller->fds[poller->amount - 1];
    poller->amount--;
}
