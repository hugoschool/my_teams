/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save_users.c
*/

#include "server/database.h"

static void save_user(FILE *database_file, user_data_t *user_data)
{
    fprintf(database_file, "%s,\"%s\",%d\n", user_data->uuid, user_data->username, user_data->status);
}

void save_users(FILE *database_file, users_t *users)
{
    fprintf(database_file, "users\n");

    for (size_t i = 0; i < users->amount; i++) {
        save_user(database_file, users->users[i]);
    }
}
