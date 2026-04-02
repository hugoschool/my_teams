/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** server.h
*/

#ifndef MY_TEAMS_SERVER_H_
    #define MY_TEAMS_SERVER_H_

    #include "args.h"
    #include <netinet/in.h>

    #define CRLF "\r\n"

// This initial amount macro can be reused for poller and clients array
// It is initially set to this amount for:
// - the initial control socket
// - the signal file descriptor handler.
    #define INITIAL_AMOUNT 2

    #define BUFFER_SIZE 4096

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
void poller_set_init_values(poller_t *poller, int socket_fd, int signal_fd);
void poller_free(poller_t *poller);

// Socket
int socket_init(in_port_t port);

// Clients
typedef enum {
    LOGGED_OUT,
    LOGGED_IN
} login_step_t;

typedef struct {
    // Pointer to its struct pollfd file descriptor
    int *fd;
    login_step_t login_step;

    // TODO: Commenting it for now
    // buffer_t *buffer;
} client_data_t;

client_data_t *client_data_init(int *fd);
void client_data_free(client_data_t *data);

typedef struct {
    client_data_t **clients;
    unsigned int amount;
    unsigned int size;
} clients_t;

    #define CLIENTS_INIT_SIZE 50

clients_t *clients_init(void);
void clients_adder(clients_t *clients, int *fd);
void clients_delete(clients_t *clients, int i);
void clients_free(clients_t *clients);

// Server
typedef struct {
    poller_t *poller;
    clients_t *clients;
    // CONTROL socket aka the main server socket
    int control_fd;
    // Handles the SIGINT (Ctrl + C)
    int signal_fd;
    // Represents the current client index that is being handled.
    unsigned int index;
} server_t;

bool teams_server(args_t *args);
void server_free(server_t *server);
void poll_handler(server_t *server, bool *running);

#endif
