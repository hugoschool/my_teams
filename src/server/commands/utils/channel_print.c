/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** channel_print.c
*/

#include "server/server.h"
#include <stdio.h>
#include <string.h>

extern inline void channel_print(int fd, channel_data_t *channel)
{
    dprintf(fd, "%s %ld %ld %s %s\n", channel->uuid,
        strlen(channel->name), strlen(channel->description),
        channel->name, channel->description);
}
