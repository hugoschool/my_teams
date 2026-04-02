/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** server.h
*/

#ifndef MY_TEAMS_SERVER_H_
    #define MY_TEAMS_SERVER_H_

    #include "args.h"
    #include "common.h"
    #include <netinet/in.h>
    #include <uuid/uuid.h>

// This initial amount macro can be reused for poller and clients array
// It is initially set to this amount for:
// - the initial control socket
// - the signal file descriptor handler.
    #define INITIAL_AMOUNT 2

// This initial size macro refers to the base size used by dynamic arrays
    #define INITIAL_SIZE 50 + INITIAL_AMOUNT

    #define BUFFER_SIZE 4096

    #define CLIENT server->clients->clients[server->index]

// For all dynamic arrays (this one and all future ones):
// amount: current amount of elements in the array
// size: actual malloc'd size of the array

// Poller
typedef struct {
    struct pollfd *fds;
    unsigned int amount;
    unsigned int size;
} poller_t;


poller_t *poller_init(void);
void poller_fd_add(poller_t *poller, int fd);
void poller_fd_delete(poller_t *poller, int i);
void poller_set_init_values(poller_t *poller, int socket_fd, int signal_fd);
void poller_free(poller_t *poller);

// Socket
int socket_init(in_port_t port);

// Users
typedef struct {
    char uuid[UUID_STR_LEN];
    char username[MAX_NAME_LENGTH + 1];
} user_data_t;

user_data_t *user_data_init(void);
void user_data_free(user_data_t *data);

typedef struct {
    user_data_t **users;
    unsigned int amount;
    unsigned int size;
} users_t;

users_t *users_init(void);
void users_free(users_t *users);

// Threads
typedef struct {
    char uuid[UUID_STR_LEN];
    char body[MAX_BODY_LENGTH + 1];
} comment_data_t;

typedef struct {
    comment_data_t **comments;
    unsigned int amount;
    unsigned int size;
} comments_t;

// Threads
typedef struct {
    char uuid[UUID_STR_LEN];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    comments_t *comments;
} thread_data_t;

typedef struct {
    thread_data_t **threads;
    unsigned int amount;
    unsigned int size;
} threads_t;

// Channels
typedef struct {
    char uuid[UUID_STR_LEN];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    threads_t *threads;
} channel_data_t;

typedef struct {
    channel_data_t **channels;
    unsigned int amount;
    unsigned int size;
} channels_t;

// Teams
typedef struct {
    char uuid[UUID_STR_LEN];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    // TODO: maybe a list of all users subscribed to the team
    channels_t *channels;
} team_data_t;

typedef struct {
    team_data_t **teams;
    unsigned int amount;
    unsigned int size;
} teams_t;

// Clients
typedef enum {
    LOGGED_OUT,
    LOGGED_IN
} login_step_t;

typedef struct {
    // Pointer to its struct pollfd file descriptor
    int *fd;
    login_step_t login_step;

    // Pointer to its user data in the main server struct
    user_data_t *user;

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

clients_t *clients_init(void);
void clients_adder(clients_t *clients, int *fd);
void clients_delete(clients_t *clients, int i);
void clients_free(clients_t *clients);

// Server
typedef struct {
    poller_t *poller;
    clients_t *clients;

    users_t *users;
    teams_t *teams;

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
