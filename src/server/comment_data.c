/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** comment_data.c
*/

#include "common.h"
#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

comment_data_t *comment_data_init(char *uuid, char *user_uuid, char *body)
{
    comment_data_t *data = malloc(sizeof(comment_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    strncpy(data->uuid, uuid, UUID_STR_LEN);
    strncpy(data->user_uuid, user_uuid, UUID_STR_LEN);
    strncpy(data->body, body, MAX_BODY_LENGTH + 1);
    data->timestamp = time(NULL);
    return data;
}

void comment_data_free(comment_data_t *data)
{
    if (data == NULL)
        return;
    free(data);
    data = NULL;
}
