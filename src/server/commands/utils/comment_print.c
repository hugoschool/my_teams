/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** comment_print.c
*/

#include "server/server.h"
#include "server/status.h"
#include <stdio.h>
#include <string.h>

void comment_print(int fd, comment_data_t *comment, int code)
{
    if (code > 0) {
        dprintf(fd, "%s" CRLF "%s %s %ld %ld %s\n", get_status(code),
            comment->uuid, comment->user_uuid,
            comment->timestamp, strlen(comment->body), comment->body);
    } else {
        dprintf(fd, "%s %s %ld %ld %s\n", comment->uuid, comment->user_uuid,
            comment->timestamp, strlen(comment->body), comment->body);
    }
}
