/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** channel_print.c
*/

#include "server/server.h"
#include "server/status.h"
#include <stdio.h>
#include <string.h>

void channel_print(int fd, channel_data_t *channel, int code)
{
    if (code > 0) {
        dprintf(fd, "%s" CRLF "%s %ld %ld %s %s\n", get_status(code),
            channel->uuid, strlen(channel->name), strlen(channel->description),
            channel->name, channel->description);
    } else {
        dprintf(fd, "%s %ld %ld %s %s\n", channel->uuid,
            strlen(channel->name), strlen(channel->description),
            channel->name, channel->description);
    }
}
