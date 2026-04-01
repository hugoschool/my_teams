/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** server.h
*/

#ifndef MY_TEAMS_SERVER_H_
    #define MY_TEAMS_SERVER_H_

    #include "args.h"

// For all dynamic arrays (this one and all future ones):
// amount: current amount of elements in the array
// size: actual malloc'd size of the array

// Poller
typedef struct {
    struct pollfd *fds;
    unsigned int amount;
    unsigned int size;
} poller_t;

    #define POLLER_INIT_SIZE 50

poller_t *poller_init(void);
void poller_fd_add(poller_t *poller, int fd);
void poller_fd_delete(poller_t *poller, int i);
void poller_set_init_socket(poller_t *poller, int socket_fd);
void poller_free(poller_t *poller);

// Server
typedef struct {
    poller_t *poller;
    // Represents the current client index that is being handled.
    unsigned int index;
} server_t;

bool teams_server(args_t *args);

#endif
