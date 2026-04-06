/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** thread_data.c
*/

#include "common.h"
#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

thread_data_t *thread_data_init(char *uuid, char *title, char *description)
{
    thread_data_t *data = malloc(sizeof(thread_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    strncpy(data->uuid, uuid, UUID_STR_LEN);
    strncpy(data->title, title, MAX_NAME_LENGTH + 1);
    strncpy(data->description, description, MAX_DESCRIPTION_LENGTH + 1);
    data->comments = NULL;
    data->timestamp = time(NULL);
    return data;
}

void thread_data_free(thread_data_t *data)
{
    if (data == NULL)
        return;
    if (data->comments)
        comments_free(data->comments);
    free(data);
    data = NULL;
}

thread_data_t *threads_get_from_uuid(threads_t *threads, char *uuid)
{
    if (threads == NULL)
        return NULL;
    for (unsigned int i = 0; i < threads->amount; i++) {
        if (strncmp(threads->threads[i]->uuid, uuid, UUID_STR_LEN) == 0)
            return threads->threads[i];
    }
    return NULL;
}

thread_data_t *threads_get_from_title(threads_t *threads, char *title)
{
    if (threads == NULL)
        return NULL;
    for (unsigned int i = 0; i < threads->amount; i++) {
        if (strncmp(threads->threads[i]->title, title, MAX_NAME_LENGTH + 1) == 0)
            return threads->threads[i];
    }
    return NULL;
}

comment_data_t *thread_add_comment(thread_data_t *thread, char *user_uuid, char *body)
{
    if (thread == NULL)
        return NULL;
    if (thread->comments == NULL)
        thread->comments = comments_init();
    return comments_add(thread->comments, user_uuid, body);
}
