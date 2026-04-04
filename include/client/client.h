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

    typedef struct client_s {
        int socket_fd;
        bool logged;
        struct sockaddr_in sockaddr;
        char *uuid;
    } client_t;

bool teams_client(client_args_t *args);

#endif