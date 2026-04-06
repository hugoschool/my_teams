/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** comments.c
*/

#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <uuid/uuid.h>

comments_t *comments_init(void)
{
    comments_t *comments = malloc(sizeof(comments_t));

    if (comments == NULL)
        return NULL;
    comments->comments = calloc(INITIAL_SIZE, sizeof(comment_data_t));
    comments->amount = 0;
    comments->size = INITIAL_SIZE;
    return comments;
}

void comments_free(comments_t *comments)
{
    if (comments == NULL)
        return;
    for (size_t i = 0; i < comments->amount; i++) {
        comment_data_free(comments->comments[i]);
    }
    free(comments->comments);
    free(comments);
}

static void comments_reallocate_size(comments_t *comments)
{
    if (comments == NULL)
        return;
    if (comments->amount == comments->size) {
        comments->size *= 2;
        comments->comments =
            realloc(comments->comments, sizeof(comment_data_t) * (comments->size));
        if (comments->comments == NULL) {
            perror("realloc");
            exit(84);
        }
    }
}

comment_data_t *comments_add(comments_t *comments, char *user_uuid, char *body)
{
    uuid_t binuuid;
    char uuid[UUID_STR_LEN];

    if (comments == NULL)
        return NULL;
    comments_reallocate_size(comments);
    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, uuid);
    comments->comments[comments->amount] = comment_data_init(uuid, user_uuid, body);
    comments->amount++;
    return comments->comments[comments->amount - 1];
}
