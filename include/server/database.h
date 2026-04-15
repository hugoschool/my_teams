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
    #include <string.h>
    #include <stdlib.h>

    #define DATABASE_PATH ".database.neige"

// Save

/* SAVE FORMAT
users
uuid"username"
... more users
end users
messages
user_uuid_from"user_uuid_to"body"timestamp
... more messages
end messages
teams
team_uuid:"name","description"
users:user_uuid,... more user_uuid
{channel_uuid}:"name","description"
(thread_uuid):user_uuid,"title","description",timestamp
[comment_uuid]:user_uuid,"body",timestamp
... more comment
[end]
... more threads
(end)
... more channels
{end}
... more teams
end teams
*/

void save(server_t *server);

void save_users(FILE *database_file, users_t *users);
void save_messages(FILE *database_file, messages_t *messages);
void save_teams(FILE *database_file, teams_t *teams);
void save_channels(FILE *database_file, channels_t *channels);
void save_threads(FILE *database_file, threads_t *threads);
void save_comments(FILE *database_file, comments_t *comments);

// Load

void load_database(server_t *server);

void load_users(FILE *database_file, users_t *users);
void load_messages(FILE *database_file, messages_t *messages);
void load_teams(FILE *database_file, teams_t *teams, users_t *users);
void load_channels(FILE *database_file, channels_t *channels);
void load_threads(FILE *database_file, threads_t *threads);
void load_comments(FILE *database_file, comments_t *comments);

#endif
