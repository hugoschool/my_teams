/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** args.c
*/

#include "server/args.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static void parse_help(void)
{
    printf("USAGE: ./myteams_server port\n\n"
        "port is the port number on which the server socket listens\n");
}

args_t parse_args(int argc, char **argv)
{
    int port = -1;

    if (argc == 2 && (strcmp(argv[1], "--help") == 0
            || strcmp(argv[1], "-h") == 0)) {
        parse_help();
        return (args_t){
            .port = -1, .help = true, .valid = true,
        };
    }
    if (argc == 2) {
        port = atoi(argv[1]);
        return (args_t){
            .port = port, .help = false, .valid = true,
        };
    }
    return (args_t){.valid = false};
}
