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
    #include <stdlib.h>

    #define DATABASE_PATH ".database"

void save(server_t *server);

void save_users(users_t *users);

#endif
