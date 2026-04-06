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
    #define CLIENT_I(i) server->clients->clients[i]

    #define USER_I(i) server->users->users[i]

    #define MESSAGE_I(i) server->messages->messages[i]

    #define TEAM_I(i) server->teams->teams[i]

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
    bool status;
} user_data_t;

user_data_t *user_data_init(char *uuid, char *username);
void user_data_free(user_data_t *data);

typedef struct {
    user_data_t **users;
    unsigned int amount;
    unsigned int size;
} users_t;

users_t *users_init(void);
void users_free(users_t *users, bool should_free);

user_data_t *users_add(users_t *users, char *username);
void users_add_data(users_t *users, user_data_t *data);

user_data_t *users_get_from_username(users_t *users, char *username);
user_data_t *users_get_from_uuid(users_t *users, char *uuid);

void users_remove_by_data(users_t *users, user_data_t *data);

// Comments
typedef struct {
    char uuid[UUID_STR_LEN];
    char user_uuid[UUID_STR_LEN];
    char body[MAX_BODY_LENGTH + 1];
    time_t timestamp;
} comment_data_t;

comment_data_t *comment_data_init(char *uuid, char *user_uuid, char *body);
void comment_data_free(comment_data_t *data);

typedef struct {
    comment_data_t **comments;
    unsigned int amount;
    unsigned int size;
} comments_t;

comments_t *comments_init(void);
void comments_free(comments_t *comments);

comment_data_t *comments_add(comments_t *comments, char *user_uuid, char *body);

// Threads
typedef struct {
    char uuid[UUID_STR_LEN];
    char title[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    comments_t *comments;
    time_t timestamp;
} thread_data_t;

thread_data_t *thread_data_init(char *uuid, char *title, char *description);
void thread_data_free(thread_data_t *data);

typedef struct {
    thread_data_t **threads;
    unsigned int amount;
    unsigned int size;
} threads_t;

threads_t *threads_init(void);
void threads_free(threads_t *threads);

thread_data_t *threads_add(threads_t *threads, char *title, char *description);
comment_data_t *thread_add_comment(thread_data_t *thread, char *user_uuid, char *body);

thread_data_t *threads_get_from_uuid(threads_t *threads, char *uuid);
thread_data_t *threads_get_from_title(threads_t *threads, char *title);

// Channels
typedef struct {
    char uuid[UUID_STR_LEN];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    threads_t *threads;
} channel_data_t;

channel_data_t *channel_data_init(char *uuid, char *name, char *description);
void channel_data_free(channel_data_t *data);

typedef struct {
    channel_data_t **channels;
    unsigned int amount;
    unsigned int size;
} channels_t;

channels_t *channels_init(void);
void channels_free(channels_t *channels);

channel_data_t *channels_add(channels_t *channels, char *name, char *description);
thread_data_t *channel_add_thread(channel_data_t *channel, char *title,
    char *description);

channel_data_t *channels_get_from_uuid(channels_t *channels, char *uuid);
channel_data_t *channels_get_from_name(channels_t *channels, char *name);

// Teams
typedef struct {
    char uuid[UUID_STR_LEN];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    // A list of the users subscribed to this team
    users_t *users;
    channels_t *channels;
} team_data_t;

team_data_t *team_data_init(char *uuid, char *name, char *description);
void team_data_free(team_data_t *data);

channel_data_t *team_add_channel(team_data_t *team, char *name,
    char *description);

typedef struct {
    team_data_t **teams;
    unsigned int amount;
    unsigned int size;
} teams_t;

teams_t *teams_init(void);
void teams_free(teams_t *teams);

team_data_t *teams_add(teams_t *teams, char *name, char *description);

team_data_t *teams_get_from_uuid(teams_t *teams, char *uuid);
team_data_t *teams_get_from_name(teams_t *teams, char *name);

bool team_is_user_subscribed(team_data_t *team, user_data_t *user);

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
void client_set_user(client_data_t *data, user_data_t *user_data);

typedef struct {
    client_data_t **clients;
    unsigned int amount;
    unsigned int size;
} clients_t;

clients_t *clients_init(void);
void clients_adder(clients_t *clients, int *fd);
void clients_delete(clients_t *clients, int i);
void clients_free(clients_t *clients);

// Message
typedef struct {
    const char *user_uuid_from;
    const char *user_uuid_to;
    char body[MAX_BODY_LENGTH + 1];
    time_t timestamp;
} message_data_t;

message_data_t *message_data_init(const char *from, const char *to,
    char *body);
void message_data_free(message_data_t *data);

typedef struct {
    message_data_t **messages;
    unsigned int amount;
    unsigned int size;
} messages_t;

messages_t *messages_init(void);
message_data_t *messages_add(messages_t *messages, char *from, char *to,
    char *body);
void messages_free(messages_t *messages);

// Server
typedef struct {
    poller_t *poller;
    clients_t *clients;

    users_t *users;
    messages_t *messages;
    teams_t *teams;

    // CONTROL socket aka the main server socket
    int control_fd;
    // Handles the SIGINT (Ctrl + C)
    int signal_fd;
    // Represents the current client index that is being handled.
    unsigned int index;
    // Represents the current client's buffer being handled.
    char *buffer;
} server_t;

bool teams_server(args_t *args);
void server_free(server_t *server);
void client_quit(server_t *server);
void poll_handler(server_t *server, bool *running);

#endif
