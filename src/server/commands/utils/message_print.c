/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** message_print.c
*/

#include "server/server.h"
#include <stdio.h>
#include <string.h>

extern inline void message_print(int fd, message_data_t *message)
{
    dprintf(fd, "%s %ld %ld %s\n", message->user_uuid_from,
        message->timestamp, strlen(message->body), message->body);
}
