/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save_channels.c
*/

#include "server/database.h"

static void save_channel(FILE *database_file, channel_data_t *channel_data)
{
    fprintf(database_file, "{%s}:\"%s\",\"%s\"\n", channel_data->uuid, channel_data->name,channel_data->description);

    save_threads(database_file, channel_data->threads);
}

void save_channels(FILE *database_file, channels_t *channels)
{
    for (size_t i = 0; i < channels->amount; i++) {
        save_channel(database_file, channels->channels[i]);
    }

    fprintf(database_file, "{end}\n");
}
