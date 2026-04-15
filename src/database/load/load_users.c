/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** load_users.c
*/

#include "server/database.h"

static void load_user(char *line, users_t *users)
{
    user_data_t *user_data;

    char uuid[UUID_STR_LEN] = {0};
    char username[MAX_NAME_LENGTH + 1] = {0};

    sscanf(line, "%[^\"]\"%[^\"]\"\n", uuid, username);

    user_data = users_add(users, username);
    strncpy(user_data->uuid, uuid, UUID_STR_LEN);
}

void load_users(FILE *database_file, users_t *users)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, database_file) != -1) {
        if (strcmp(line, "end users\n") == 0) {
            break;
        }
        load_user(line, users);
    }

    if (line) {
        free(line);
    }
}
