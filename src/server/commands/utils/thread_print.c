/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** thread_print.c
*/

#include "server/server.h"
#include <stdio.h>
#include <string.h>

extern inline void thread_print(int fd, thread_data_t *thread)
{
    dprintf(fd, "%s %s %ld %ld %ld %s %s\n", thread->uuid,
        thread->user_uuid, thread->timestamp,
        strlen(thread->title), strlen(thread->description),
        thread->title, thread->description);
}
