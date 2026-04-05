/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** messages.c
*/

#include "server/server.h"
#include "server/status.h"
#include <stdio.h>
#include <stdlib.h>

void command_teams(server_t *server)
{
    team_data_t *team = NULL;

    WRITE_STATUS(*CLIENT->fd, 200);
    for (unsigned int i = 0; i < server->teams->amount; i++) {
        team = TEAM_I(i);
        dprintf(*CLIENT->fd, "%s %s %s\n", team->name, team->uuid,
            team->description);
    }
}
