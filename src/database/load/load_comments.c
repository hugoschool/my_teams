/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** load_comment.c
*/

#include "server/database.h"

static void load_comment(char *line, comments_t *comments)
{
    comment_data_t *comment_data;

    char uuid[UUID_STR_LEN] = {0};
    char user_uuid[UUID_STR_LEN] = {0};
    char body[MAX_BODY_LENGTH + 1] = {0};
    time_t timestamp;

    sscanf(line, "(%s):%s,\"%s\",%ld\n", uuid, user_uuid, body, &timestamp);

    comment_data = comments_add(comments, user_uuid, body);
    strncpy(comment_data->uuid, uuid, UUID_STR_LEN);
    comment_data->timestamp = timestamp;
}

void load_comments(FILE *database_file, comments_t *comments)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, database_file) != -1) {
        if (strcmp(line, "[end]\n") == 0) {
            break;
        }
        load_comment(line, comments);
    }

    if (line) {
        free(line);
    }
}
