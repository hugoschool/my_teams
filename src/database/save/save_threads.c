/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save_threads.c
*/

#include "server/database.h"

static void save_thread(FILE *database_file, thread_data_t *thread_data)
{
    fprintf(database_file, "(%s):%s,\"%s\",\"%s\",%ld\n", thread_data->uuid, thread_data->user_uuid, thread_data->title, thread_data->description, thread_data->timestamp);

    save_comments(database_file, thread_data->comments);
}

void save_threads(FILE *database_file, threads_t *threads)
{
    if (threads == NULL)
        return;

    for (size_t i = 0; i < threads->amount; i++) {
        save_thread( database_file, threads->threads[i]);
    }

    fprintf(database_file, "(end)\n");
}

