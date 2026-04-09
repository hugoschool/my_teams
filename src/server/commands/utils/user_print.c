/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** user_print.c
*/

#include "server/server.h"
#include <stdio.h>

extern inline void user_print(int fd, user_data_t *user)
{
    dprintf(fd, "%s %s %d\n", user->username, user->uuid,
        user->status);
}
