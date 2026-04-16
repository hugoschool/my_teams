/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save.c
*/

#include "server/database.h"

void save(server_t * server)
{
    FILE *database_file = fopen(DATABASE_PATH, "w+");

    save_users(database_file, server->users);
    save_messages(database_file, server->messages);
    save_teams(database_file, server->teams);

    fclose(database_file);
}
