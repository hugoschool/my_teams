/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** args.c
*/

#include "client/args.h"
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static void parse_help(void)
{
    printf("USAGE: ./myteams_cli ip port\n\n"
        "ip is the server ip address on which the server socket listens\n"
        "port is the port number on which the server socket listens\n");
}

client_args_t parse_args(int argc, char **argv)
{
    int port = -1;
    in_addr_t ip = 0;

    if (argc == 2 && (strcmp(argv[1], "--help") == 0
            || strcmp(argv[1], "-h") == 0)) {
        parse_help();
        return (client_args_t){
            .port = -1, .ip = 0, .help = true, .valid = true,
        };
    }
    if (argc == 3) {
        ip = inet_addr(argv[1]);
        if (ip == INADDR_NONE) {
            return (client_args_t){
                .port = port, .ip = 0, .help = false, .valid = false,
            };
        }
        port = atoi(argv[2]);
        return (client_args_t){
            .port = port, .ip = ip, .help = false, .valid = true,
        };
    }
    return (client_args_t){.valid = false};
}
