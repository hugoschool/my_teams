/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** user_data.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

user_data_t *user_data_init(void)
{
    user_data_t *data = malloc(sizeof(user_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    memset(data->uuid, '0', UUID_STR_LEN);
    memset(data->username, '0', MAX_NAME_LENGTH + 1);
    return data;
}

void user_data_free(user_data_t *data)
{
    if (data == NULL)
        return;
    free(data);
    data = NULL;
}
