/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** messages.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>

messages_t *messages_init(void)
{
    messages_t *messages = malloc(sizeof(messages_t));

    if (messages == NULL) {
        perror("malloc");
        exit(84);
    }
    messages->messages = calloc(INITIAL_SIZE, sizeof(message_data_t));
    if (messages->messages == NULL) {
        perror("calloc");
        exit(84);
    }
    messages->amount = 0;
    messages->size = INITIAL_SIZE;
    return messages;
}

void messages_free(messages_t *messages)
{
    if (messages == NULL)
        return;
    for (size_t i = 0; i < messages->amount; i++) {
        message_data_free(messages->messages[i]);
    }
    free(messages->messages);
    free(messages);
}

message_data_t *messages_add(messages_t *messages, char *from, char *to,
    char *body)
{
    if (messages == NULL)
        return NULL;
    if (messages->amount == messages->size) {
        messages->size *= 2;
        messages->messages =
            realloc(messages->messages, sizeof(message_data_t) * (messages->size));
        if (messages->messages == NULL) {
            perror("realloc");
            exit(84);
        }
    }
    messages->messages[messages->amount] = message_data_init(from, to, body);
    messages->amount++;
    return messages->messages[messages->amount - 1];
}
