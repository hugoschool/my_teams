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
    fprintf(database_file, "(end)\n");
}

void save_threads(FILE *database_file, threads_t *threads)
{
    for (size_t i = 0; i < threads->amount; i++) {
        save_thread( database_file, threads->threads[i]);
    }
}

char uuid[UUID_STR_LEN];
char user_uuid[UUID_STR_LEN];
char title[MAX_NAME_LENGTH + 1];
char description[MAX_DESCRIPTION_LENGTH + 1];
comments_t *comments;
time_t timestamp;