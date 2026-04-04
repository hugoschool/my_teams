/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** message_data.c
*/

#include "common.h"
#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

message_data_t *message_data_init(const char *from, const char *to, char *body)
{
    message_data_t *data = malloc(sizeof(message_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    data->user_uuid_from = strdup(from);
    data->user_uuid_to = strdup(to);
    strncpy(data->body, body, MAX_BODY_LENGTH + 1);
    return data;
}

void message_data_free(message_data_t *data)
{
    if (data == NULL)
        return;
    free((void *)data->user_uuid_from);
    free((void *)data->user_uuid_to);
    free(data);
}
