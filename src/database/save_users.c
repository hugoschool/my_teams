/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save_users.c
*/

#include "server/database.h"

static void save_user(FILE *file, user_data_t *user_data)
{
    fprintf(file, "%s, %s, %d\n", user_data->uuid, user_data->username, user_data->status);
}

void save_users(users_t *users)
{
    FILE *file = fopen(DATABASE_PATH "/users.neige", "w");

    if (!file) {
        return;
    }
    for (size_t i = 0; i < users->amount; i++) {
        save_user(file, users->users[i]);
    }
    fclose(file);
}
