/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** load_messages.c
*/

#include "server/database.h"

static void load_message(char *line, messages_t *messages)
{
    message_data_t *message_data;

    char user_uuid_from[UUID_STR_LEN] = {0};
    char user_uuid_to[UUID_STR_LEN] = {0};
    char body[MAX_BODY_LENGTH + 1] = {0};
    time_t timestamp;

    sscanf(line, "%s,%s,\"%s\",%ld\n", user_uuid_from, user_uuid_to, body, &timestamp);

    message_data = messages_add(messages, user_uuid_from, user_uuid_to, body);;
    message_data->timestamp = timestamp;
}

void load_messages(FILE *database_file, messages_t *messages)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, database_file) != -1) {
        if (strcmp(line, "end messages\n") == 0) {
            break;
        }
        load_message(line, messages);
    }

    if (line) {
        free(line);
    }
}
