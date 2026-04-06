/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** channels.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <uuid/uuid.h>

channels_t *channels_init(void)
{
    channels_t *channels = malloc(sizeof(channels_t));

    if (channels == NULL)
        return NULL;
    channels->channels = calloc(INITIAL_SIZE, sizeof(channel_data_t));
    channels->amount = 0;
    channels->size = INITIAL_SIZE;
    return channels;
}

void channels_free(channels_t *channels)
{
    if (channels == NULL)
        return;
    for (size_t i = 0; i < channels->amount; i++) {
        channel_data_free(channels->channels[i]);
    }
    free(channels->channels);
    free(channels);
}

static void channels_reallocate_size(channels_t *channels)
{
    if (channels == NULL)
        return;
    if (channels->amount == channels->size) {
        channels->size *= 2;
        channels->channels =
            realloc(channels->channels, sizeof(channel_data_t) * (channels->size));
        if (channels->channels == NULL) {
            perror("realloc");
            exit(84);
        }
    }
}

channel_data_t *channels_add(channels_t *channels, char *name, char *description)
{
    uuid_t binuuid;
    char uuid[UUID_STR_LEN];

    if (channels == NULL)
        return NULL;
    channels_reallocate_size(channels);
    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, uuid);
    channels->channels[channels->amount] = channel_data_init(uuid, name, description);
    channels->amount++;
    return channels->channels[channels->amount - 1];
}
