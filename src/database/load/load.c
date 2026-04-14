/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** load.c
*/

#include "server/database.h"

void load_database(server_t * server)
{
    FILE *database_file = fopen(DATABASE_PATH, "r");
    char *line = NULL;
    size_t len = 0;

    if (database_file == NULL) {
        return;
    }

    while (getline(&line, &len, database_file)) {
        if (strcmp(line, "users\n") == 0) {
            load_users(database_file, server->users);
        }
        if (strcmp(line, "messages\n") == 0) {
            load_messages(database_file, server->messages);
        }
        if (strcmp(line, "teams\n") == 0) {
            load_teams(database_file, server->teams, server->users);
        }
    }

    if (line) {
        free(line);
    }
}
