/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** user.c
*/

#include "server/server.h"
#include <stdlib.h>

users_t *users_init(void)
{
    users_t *users = malloc(sizeof(users_t));

    if (users == NULL)
        return NULL;
    users->users = calloc(INITIAL_SIZE, sizeof(user_data_t));
    users->amount = 0;
    users->size = INITIAL_SIZE;
    return users;
}

void users_free(users_t *users)
{
    if (users == NULL)
        return;
    for (size_t i = 0; i < users->amount; i++) {
        user_data_free(users->users[i]);
    }
    free(users->users);
    free(users);
}
