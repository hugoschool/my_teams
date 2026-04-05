/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** team_data.c
*/

#include "common.h"
#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

team_data_t *team_data_init(char *uuid, char *name, char *description)
{
    team_data_t *data = malloc(sizeof(team_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    strncpy(data->uuid, uuid, UUID_STR_LEN);
    strncpy(data->name, name, MAX_NAME_LENGTH + 1);
    strncpy(data->description, description, MAX_DESCRIPTION_LENGTH + 1);
    data->users = users_init();
    if (data->users == NULL)
        exit(84);
    data->channels = NULL;
    return data;
}

void team_data_free(team_data_t *data)
{
    if (data == NULL)
        return;
    free(data);
    data = NULL;
}

team_data_t *teams_get_from_uuid(teams_t *teams, char *uuid)
{
    for (unsigned int i = 0; i < teams->amount; i++) {
        if (strncmp(teams->teams[i]->uuid, uuid, UUID_STR_LEN) == 0)
            return teams->teams[i];
    }
    return NULL;
}

team_data_t *teams_get_from_name(teams_t *teams, char *name)
{
    for (unsigned int i = 0; i < teams->amount; i++) {
        if (strncmp(teams->teams[i]->name, name, MAX_NAME_LENGTH + 1) == 0)
            return teams->teams[i];
    }
    return NULL;
}

bool team_is_user_subscribed(team_data_t *team, user_data_t *user)
{
    user_data_t *team_user = NULL;

    for (unsigned int i = 0; i < team->users->amount; i++) {
        team_user = team->users->users[i];
        if (team_user == user) {
            return true;
        }
    }
    return false;
}
