/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** create_text.c
*/

#include "server/server.h"
#include "server/status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Ignoring encoding for now
void command_create_text(server_t *server)
{
    char *bytes_arg = get_arg(server->buffer, 2);
    size_t bytes = 0;
    char *body = NULL;
    text_data_t *text = NULL;

    if (bytes_arg == NULL) {
        WRITE_STATUS(*CLIENT->fd, 499);
        return;
    }
    bytes = atoi(bytes_arg);
    free(bytes_arg);
    body = read_bytes_from_arg_nb(server->buffer, 3, 10);
    if (body == NULL) {
        WRITE_STATUS(*CLIENT->fd, 499);
        return;
    }
    text = texts_add(server->texts, body, bytes);
    free(body);
    WRITE_STATUS(*CLIENT->fd, 200);
    dprintf(*CLIENT->fd, "%s\n", text->uuid);
}
