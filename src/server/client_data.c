/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** client_data.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

client_data_t *client_data_init(int *fd)
{
    client_data_t *data = malloc(sizeof(client_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    data->fd = fd;
    data->login_step = LOGGED_OUT;
    data->user = NULL;
    return data;
}

void client_data_free(client_data_t *data)
{
    if (data == NULL)
        return;
    free(data);
    data = NULL;
}

void client_set_user(client_data_t *data, user_data_t *user_data)
{
    if (data == NULL)
        return;
    data->user = user_data;
}
