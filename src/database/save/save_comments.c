/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** save_comments.c
*/

#include "server/database.h"

static void save_comment(FILE *database_file, comment_data_t *comment_data)
{
    fprintf(database_file, "[%s\"%s\"%s\"%ld\"]\n", comment_data->uuid, comment_data->user_uuid,comment_data->body, comment_data->timestamp);
}

void save_comments(FILE *database_file, comments_t *comments)
{
    for (size_t i = 0; comments && i < comments->amount; i++) {
        save_comment(database_file, comments->comments[i]);
    }

    fprintf(database_file, "[end]\n");
}
