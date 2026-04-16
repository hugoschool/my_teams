/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** user_print.c
*/

#include "server/server.h"
#include "server/status.h"
#include <stdio.h>

void user_print(int fd, user_data_t *user, int code)
{
    if (code > 0) {
        dprintf(fd, "%s" CRLF "%s %s %d\n", get_status(code),
            user->username, user->uuid, user->status);
    } else {
        dprintf(fd, "%s %s %d\n", user->username, user->uuid,
            user->status);
    }
}
