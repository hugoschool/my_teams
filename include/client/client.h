/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** client.h
*/

#ifndef MY_TEAMS_CLIENT_H_
    #define MY_TEAMS_CLIENT_H_

    #include "client/args.h"
    #include <netinet/in.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <uuid/uuid.h>
    #include <string.h>
    #include "common.h"
    #include "utils.h"

    #define BIG_BUFFER_SIZE 4096

    typedef struct context_s {
        char team_uuid[UUID_STR_LEN];
        char channel_uuid[UUID_STR_LEN];
        char thread_uuid[UUID_STR_LEN];
    } context_t;

    typedef struct sub_teams_s {
        char **team_uuid;
        int amount;
        int team_index;
    } sub_teams_t;

    typedef struct client_s {
        int socket_fd;
        bool logged;
        struct sockaddr_in sockaddr;
        char uuid[UUID_STR_LEN];
        char user_name[MAX_NAME_LENGTH];
        context_t context;
        char buffer[BIG_BUFFER_SIZE];
        sub_teams_t *subscribed_teams;
    } client_t;

bool teams_client(client_args_t *args);
ssize_t receive(client_t *client, size_t bytes_to_recv);
void command_parser(char *command, client_t *client);
char *craft_command(char *command);
#endif