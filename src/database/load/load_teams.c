/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** load_teams.c
*/

#include "server/database.h"

static void load_team_users(char *line, users_t *team_users, users_t *users)
{
    size_t index = strlen("users:");

    while (index < strlen(line) -1 && line[index] != '\n') {
        char uuid[UUID_STR_LEN] = {0};
        strncpy(uuid, line + index, UUID_STR_LEN - 1);

        users_add_data(team_users, users_get_from_uuid(users, uuid));

        index += UUID_STR_LEN - 1;
        if (line[index] == ',') {
            index += 1;
        }
    }
}

static void load_team(FILE *database_file, char *line, size_t len, teams_t *teams, users_t *users)
{
    team_data_t *team_data;

    char uuid[UUID_STR_LEN] = {0};
    char name[MAX_NAME_LENGTH + 1] = {0};
    char description[MAX_DESCRIPTION_LENGTH + 1] = {0};

    sscanf(line, "\"%s\"%s\"%s\"\n", uuid, name, description);

    team_data = teams_add(teams, name, description);
    strncpy(team_data->uuid, uuid, UUID_STR_LEN);

    // team users
    if (getline(&line, &len, database_file) == -1) {
        return;
    }
    load_team_users(line, team_data->users, users);

    load_channels(database_file, team_data->channels);
}

void load_teams(FILE *database_file, teams_t *teams, users_t *users)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, database_file) != -1) {
        if (strcmp(line, "end teams\n") == 0) {
            break;
        }
        load_team(database_file, line, len, teams, users);
    }

    if (line) {
        free(line);
    }
}
