/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** user_data.c
*/

#include "common.h"
#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

user_data_t *user_data_init(char *uuid, char *username)
{
    user_data_t *data = malloc(sizeof(user_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    strncpy(data->uuid, uuid, UUID_STR_LEN);
    strncpy(data->username, username, MAX_NAME_LENGTH + 1);
    return data;
}

void user_data_free(user_data_t *data)
{
    if (data == NULL)
        return;
    free(data);
    data = NULL;
}

user_data_t *users_get_from_username(users_t *users, char *username)
{
    for (unsigned int i = 0; i < users->amount; i++) {
        if (strncmp(users->users[i]->username,
                username, MAX_NAME_LENGTH + 1) == 0)
            return users->users[i];
    }
    return NULL;
}

user_data_t *users_get_from_uuid(users_t *users, char *uuid)
{
    for (unsigned int i = 0; i < users->amount; i++) {
        if (strncmp(users->users[i]->uuid, uuid, UUID_STR_LEN) == 0)
            return users->users[i];
    }
    return NULL;
}
