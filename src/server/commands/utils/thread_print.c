/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** thread_print.c
*/

#include "server/server.h"
#include "server/status.h"
#include <stdio.h>
#include <string.h>

void thread_print(int fd, thread_data_t *thread, int code)
{
    if (code > 0) {
        dprintf(fd, "%s" CRLF "%s %s %ld %ld %ld %s %s\n", get_status(code),
            thread->uuid, thread->user_uuid, thread->timestamp,
            strlen(thread->title), strlen(thread->description),
            thread->title, thread->description);
    } else {
        dprintf(fd, "%s %s %ld %ld %ld %s %s\n",
            thread->uuid, thread->user_uuid, thread->timestamp,
            strlen(thread->title), strlen(thread->description),
            thread->title, thread->description);
    }
}
