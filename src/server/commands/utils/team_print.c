/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** team_print.c
*/

#include "server/server.h"
#include "server/status.h"
#include <stdio.h>
#include <string.h>

void team_print(int fd, team_data_t *team, int code)
{
    if (code > 0) {
        dprintf(fd, "%s" CRLF "%s %ld %ld %s %s\n", get_status(code),
            team->uuid, strlen(team->name), strlen(team->description),
            team->name, team->description);
    } else {
        dprintf(fd, "%s %ld %ld %s %s\n", team->uuid,
            strlen(team->name), strlen(team->description), team->name,
            team->description);
    }
}
