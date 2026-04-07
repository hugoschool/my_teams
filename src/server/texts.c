/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** texts.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

texts_t *texts_init(void)
{
    texts_t *texts = malloc(sizeof(texts_t));

    if (texts == NULL)
        return NULL;
    texts->texts = calloc(INITIAL_SIZE, sizeof(text_data_t));
    texts->amount = 0;
    texts->size = INITIAL_SIZE;
    return texts;
}

void texts_free(texts_t *texts)
{
    if (texts == NULL)
        return;
    for (size_t i = 0; i < texts->amount; i++) {
        text_data_free(texts->texts[i]);
    }
    free(texts->texts);
    free(texts);
}

static void texts_reallocate_size(texts_t *texts)
{
    if (texts == NULL)
        return;
    if (texts->amount == texts->size) {
        texts->size *= 2;
        texts->texts =
            realloc(texts->texts, sizeof(text_data_t) * (texts->size));
        if (texts->texts == NULL) {
            perror("realloc");
            exit(84);
        }
    }
}

text_data_t *texts_add(texts_t *texts, char *body, size_t length)
{
    if (texts == NULL)
        return NULL;
    texts_reallocate_size(texts);
    texts->texts[texts->amount] = text_data_init(body, length);
    texts->amount++;
    return texts->texts[texts->amount - 1];
}

text_data_t *texts_consume(texts_t *texts, char *uuid)
{
    text_data_t *data = NULL;

    for (unsigned int i = 0; i < texts->amount; i++) {
        data = texts->texts[i];
        if (strcmp(data->uuid, uuid) == 0) {
            texts->texts[i] = texts->texts[texts->amount - 1];
            texts->amount--;
            return data;
        }
    }
    return NULL;
}
