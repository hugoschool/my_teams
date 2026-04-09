/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** team_print.c
*/

#include "server/server.h"
#include <stdio.h>
#include <string.h>

extern inline void team_print(int fd, team_data_t *team)
{
    dprintf(fd, "%s %ld %ld %s %s\n", team->uuid,
        strlen(team->name), strlen(team->description), team->name,
        team->description);
}
