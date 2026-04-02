/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** user.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <uuid/uuid.h>

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

user_data_t *users_add(users_t *users, char *username)
{
    uuid_t binuuid;
    char uuid[UUID_STR_LEN];

    if (users == NULL)
        return NULL;
    if (users->amount == users->size) {
        users->size += 1;
        users->users =
            realloc(users->users, sizeof(user_data_t) * (users->size));
        if (users->users == NULL) {
            perror("realloc");
            exit(84);
        }
    }
    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, uuid);
    users->users[users->amount] = user_data_init(uuid, username);
    users->amount++;
    return users->users[users->amount];
}
