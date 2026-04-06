/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** channel_data.c
*/

#include "common.h"
#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

channel_data_t *channel_data_init(char *uuid, char *name, char *description)
{
    channel_data_t *data = malloc(sizeof(channel_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    strncpy(data->uuid, uuid, UUID_STR_LEN);
    strncpy(data->name, name, MAX_NAME_LENGTH + 1);
    strncpy(data->description, description, MAX_DESCRIPTION_LENGTH + 1);
    data->threads = NULL;
    return data;
}

void channel_data_free(channel_data_t *data)
{
    if (data == NULL)
        return;
    if (data->threads)
        threads_free(data->threads);
    free(data);
    data = NULL;
}

channel_data_t *channels_get_from_uuid(channels_t *channels, char *uuid)
{
    if (channels == NULL)
        return NULL;
    for (unsigned int i = 0; i < channels->amount; i++) {
        if (strncmp(channels->channels[i]->uuid, uuid, UUID_STR_LEN) == 0)
            return channels->channels[i];
    }
    return NULL;
}

channel_data_t *channels_get_from_name(channels_t *channels, char *name)
{
    if (channels == NULL)
        return NULL;
    for (unsigned int i = 0; i < channels->amount; i++) {
        if (strncmp(channels->channels[i]->name, name, MAX_NAME_LENGTH + 1) == 0)
            return channels->channels[i];
    }
    return NULL;
}

thread_data_t *channel_add_thread(channel_data_t *channel, char *title,
    char *description)
{
    if (channel == NULL)
        return NULL;
    if (channel->threads == NULL)
        channel->threads = threads_init();
    return threads_add(channel->threads, title, description);
}
