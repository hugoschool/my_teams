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
    bool status;

    sscanf(line, "%s,\"%s\",%d\n", uuid, username, (int *)&status);

    user_data = user_data_init(uuid, username);
    user_data->status = status;

    users_add_data(users,user_data);
}

void load_users(FILE *database_file, users_t *users)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, database_file)) {
        if (strcmp(line, "end users\n") == 0) {
            break;
        }
        load_user(line, users);
    }

    if (line) {
        free(line);
    }
}
