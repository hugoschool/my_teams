/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** args.h
*/

#ifndef ARGS_H_
    #define ARGS_H_

    #include <netinet/in.h>
    #include <stdbool.h>

typedef struct {
    const int port;
    const in_addr_t ip;
    bool help;
    // Must be true when the args are valid (ex: --help)
    bool valid;
} client_args_t;

client_args_t parse_args(int argc, char **argv);

#endif
