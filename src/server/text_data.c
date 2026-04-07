/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** text_data.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

text_data_t *text_data_init(char *body, size_t length)
{
    text_data_t *data = malloc(sizeof(text_data_t));
    uuid_t binuuid;
    char uuid[UUID_STR_LEN];

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, uuid);
    strncpy(data->uuid, uuid, UUID_STR_LEN);
    data->body = strdup(body);
    data->length = length;
    return data;
}

void text_data_free(text_data_t *data)
{
    if (data == NULL)
        return;
    if (data->body)
        free(data->body);
    free(data);
    data = NULL;
}
