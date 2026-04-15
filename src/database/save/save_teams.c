/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save_teams.c
*/

#include "server/database.h"

static void save_team(FILE *database_file, team_data_t *team_data)

{
    fprintf(database_file, "%-36s\"%-32s\"%-255s\"\n", team_data->uuid, team_data->name, team_data->description);

    // teams users
    fprintf(database_file, "users:");
    for (size_t i = 0; i < team_data->users->amount; i++) {
        fprintf(database_file, "%-36s", team_data->users->users[i]->uuid);
        if (i + 1 < team_data->users->amount) {
            fprintf(database_file, ",");
        }
    }
    fprintf(database_file, "\n");

    // teams channels
    save_channels(database_file, team_data->channels);
}

void save_teams(FILE *database_file, teams_t *teams)
{
    if (teams == NULL)
        return;

    fprintf(database_file, "teams\n");

    for (size_t i = 0; i < teams->amount; i++) {
        save_team(database_file, teams->teams[i]);
    }

    fprintf(database_file, "end teams\n");
}
