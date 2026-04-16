/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** message_print.c
*/

#include "server/server.h"
#include "server/status.h"
#include <stdio.h>
#include <string.h>

void message_print(int fd, message_data_t *message, int code)
{
    if (code > 0) {
        dprintf(fd, "%s" CRLF "%s %ld %ld %s\n", get_status(code),
            message->user_uuid_from,
            message->timestamp, strlen(message->body), message->body);
    } else {
        dprintf(fd, "%s %ld %ld %s\n", message->user_uuid_from,
            message->timestamp, strlen(message->body), message->body);
    }
}
