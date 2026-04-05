/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** teams.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <uuid/uuid.h>

teams_t *teams_init(void)
{
    teams_t *teams = malloc(sizeof(teams_t));

    if (teams == NULL)
        return NULL;
    teams->teams = calloc(INITIAL_SIZE, sizeof(team_data_t));
    teams->amount = 0;
    teams->size = INITIAL_SIZE;
    return teams;
}

void teams_free(teams_t *teams)
{
    if (teams == NULL)
        return;
    for (size_t i = 0; i < teams->amount; i++) {
        team_data_free(teams->teams[i]);
    }
    free(teams->teams);
    free(teams);
}

static void teams_reallocate_size(teams_t *teams)
{
    if (teams == NULL)
        return;
    if (teams->amount == teams->size) {
        teams->size *= 2;
        teams->teams =
            realloc(teams->teams, sizeof(team_data_t) * (teams->size));
        if (teams->teams == NULL) {
            perror("realloc");
            exit(84);
        }
    }
}

team_data_t *teams_add(teams_t *teams, char *name, char *description)
{
    uuid_t binuuid;
    char uuid[UUID_STR_LEN];

    if (teams == NULL)
        return NULL;
    teams_reallocate_size(teams);
    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, uuid);
    teams->teams[teams->amount] = team_data_init(uuid, name, description);
    teams->amount++;
    return teams->teams[teams->amount - 1];
}
