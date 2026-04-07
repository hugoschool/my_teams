/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** get_text.c
*/

#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void command_get_text(server_t *server)
{
    char *uuid = get_arg(server->buffer, 1);
    text_data_t *text = texts_consume(server->texts, uuid);

    free(uuid);
    if (text == NULL) {
        WRITE_STATUS(*CLIENT->fd, 460);
        return;
    }
    WRITE_STATUS(*CLIENT->fd, 200);
    dprintf(*CLIENT->fd, "%ld %s\n", text->length, text->body);
}
