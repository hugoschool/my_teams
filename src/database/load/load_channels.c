/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** load_channels.c
*/

#include "server/database.h"

static void load_channel(FILE *database_file, char *line, channels_t *channels)
{
    channel_data_t *channel_data;

    char uuid[UUID_STR_LEN] = {0};
    char name[MAX_NAME_LENGTH + 1] = {0};
    char description[MAX_DESCRIPTION_LENGTH + 1] = {0};

    sscanf(line, "{%s}:\"%s\",\"%s\"\n", uuid, name, description);

    channel_data = channels_add(channels, name, description);
    strncpy(channel_data->uuid, uuid, UUID_STR_LEN);

    load_threads(database_file, channel_data->threads);
}

void load_channels(FILE *database_file, channels_t *channels)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, database_file) != -1) {
        if (strcmp(line, "{end}\n") == 0) {
            break;
        }
        load_channel(database_file, line, channels);
    }

    if (line) {
        free(line);
    }
}
