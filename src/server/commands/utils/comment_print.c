/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** comment_print.c
*/

#include "server/server.h"
#include <stdio.h>
#include <string.h>

extern inline void comment_print(int fd, comment_data_t *comment)
{
    dprintf(fd, "%s %s %ld %ld %s\n", comment->uuid, comment->user_uuid,
        comment->timestamp, strlen(comment->body), comment->body);
}
