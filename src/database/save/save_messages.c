/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save_messages.c
*/

#include "server/database.h"

static void save_message(FILE *database_file, message_data_t *message_data)
{
    fprintf(database_file, "%-36s\"%-36s\"%-512s\"%ld\"\n", message_data->user_uuid_from, message_data->user_uuid_to, message_data->body, message_data->timestamp);
}

void save_messages(FILE *database_file, messages_t *messages)
{
    if (messages == NULL)
        return;

    fprintf(database_file, "messages\n");

    for (size_t i = 0; i < messages->amount; i++) {
        save_message(database_file, messages->messages[i]);
    }

    fprintf(database_file, "end messages\n");
}
