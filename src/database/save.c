/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save.c
*/

#include "server/database.h"

void save(server_t * server)
{
    save_users(server->users);
}
