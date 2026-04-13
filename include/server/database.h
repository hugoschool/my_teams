/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** database.h
*/

#ifndef DATABASE_H_
    #define DATABASE_H_

    #include "server/server.h"
    #include <stdio.h>

    #define DATABASE_PATH ".database.neige"

void save(server_t *server);

void save_users(FILE *database_file, users_t *users);
void save_messages(FILE *database_file, messages_t *messages);
void save_teams(FILE *database_file, teams_t *teams);

#endif
