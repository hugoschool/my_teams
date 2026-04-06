/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** threads.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <uuid/uuid.h>

threads_t *threads_init(void)
{
    threads_t *threads = malloc(sizeof(threads_t));

    if (threads == NULL)
        return NULL;
    threads->threads = calloc(INITIAL_SIZE, sizeof(thread_data_t));
    threads->amount = 0;
    threads->size = INITIAL_SIZE;
    return threads;
}

void threads_free(threads_t *threads)
{
    if (threads == NULL)
        return;
    for (size_t i = 0; i < threads->amount; i++) {
        thread_data_free(threads->threads[i]);
    }
    free(threads->threads);
    free(threads);
}

static void threads_reallocate_size(threads_t *threads)
{
    if (threads == NULL)
        return;
    if (threads->amount == threads->size) {
        threads->size *= 2;
        threads->threads =
            realloc(threads->threads, sizeof(thread_data_t) * (threads->size));
        if (threads->threads == NULL) {
            perror("realloc");
            exit(84);
        }
    }
}

thread_data_t *threads_add(threads_t *threads, char *user_uuid, char *title,
    char *description)
{
    uuid_t binuuid;
    char uuid[UUID_STR_LEN];

    if (threads == NULL)
        return NULL;
    threads_reallocate_size(threads);
    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, uuid);
    threads->threads[threads->amount] = thread_data_init(uuid, user_uuid, title, description);
    threads->amount++;
    return threads->threads[threads->amount - 1];
}
