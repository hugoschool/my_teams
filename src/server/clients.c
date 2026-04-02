/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** clients.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>

clients_t *clients_init(void)
{
    clients_t *clients = malloc(sizeof(clients_t));

    if (clients == NULL) {
        perror("malloc");
        exit(84);
    }
    clients->clients = calloc(CLIENTS_INIT_SIZE, sizeof(client_data_t));
    if (clients->clients == NULL) {
        perror("calloc");
        exit(84);
    }
    clients->amount = INITIAL_AMOUNT;
    clients->size = CLIENTS_INIT_SIZE;
    return clients;
}

void clients_adder(clients_t *clients, int *fd)
{
    if (clients == NULL)
        return;
    if (clients->amount == clients->size) {
        clients->size += 1;
        clients->clients =
            realloc(clients->clients, sizeof(client_data_t) * (clients->size));
        if (clients->clients == NULL) {
            perror("realloc");
            exit(84);
        }
    }
    clients->clients[clients->amount] = client_data_init(fd);
    clients->amount++;
}

void clients_delete(clients_t *clients, int i)
{
    if (clients == NULL || (unsigned int)i >= clients->amount
        || clients->clients[i] == NULL)
        return;
    client_data_free(clients->clients[i]);
    clients->clients[i] = clients->clients[clients->amount - 1];
    clients->amount--;
}

void clients_free(clients_t *clients)
{
    if (clients == NULL)
        return;
    for (size_t i = 0; i < clients->amount; i++) {
        client_data_free(clients->clients[i]);
    }
    free(clients->clients);
    free(clients);
}
