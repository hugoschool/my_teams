/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** subscribed.c
*/

#include "server/server.h"
#include "server/status.h"
#include <stdio.h>
#include <stdlib.h>

void command_subscribed(server_t *server)
{
    team_data_t *team = NULL;

    WRITE_STATUS(*CLIENT->fd, 200);
    for (unsigned int i = 0; i < server->teams->amount; i++) {
        team = TEAM_I(i);
        for (unsigned int user_i = 0; user_i < team->users->amount; user_i++) {
            if (CLIENT->user == team->users->users[i])
                dprintf(*CLIENT->fd, "%s %ld %ld %s %s\n", team->uuid,
                    strlen(team->name), strlen(team->description), team->name,
                    team->description);
        }
    }
}
