/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main.c
*/

#include "server/args.h"
#include "server/server.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    args_t args = parse_args(argc, argv);

    if (args.valid == false) {
        fprintf(stdout, "Invalid arguments\n");
        return 84;
    }
    if (args.help)
        return 0;
    if (!teams_server(&args))
        return 84;
    return 0;
}
