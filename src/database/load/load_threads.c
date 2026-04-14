/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** load_threads.c
*/

#include "server/database.h"

static void load_thread(FILE *database_file, char *line, threads_t *threads)
{
    thread_data_t *thread_data;

    char uuid[UUID_STR_LEN] = {0};
    char user_uuid[UUID_STR_LEN] = {0};
    char title[MAX_NAME_LENGTH + 1] = {0};
    char description[MAX_DESCRIPTION_LENGTH + 1] = {0};
    time_t timestamp;

    sscanf(line, "(%s):%s,\"%s\",\"%s\",%ld\n", uuid, user_uuid, title, description, &timestamp);

    thread_data = threads_add(threads, user_uuid, title, description);
    strcpy(thread_data->uuid, uuid);
    thread_data->timestamp = timestamp;

    load_comments(database_file, thread_data->comments);
}

void load_threads(FILE *database_file, threads_t *threads)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, database_file)) {
        if (strcmp(line, "(end)\n") == 0) {
            break;
        }
        load_thread(database_file, line, threads);
    }

    if (line) {
        free(line);
    }
}
