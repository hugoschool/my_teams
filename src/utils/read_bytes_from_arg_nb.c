/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** read_bytes_from_arg_nb.c
*/

#include <string.h>
#include <stdio.h>

char *read_bytes_from_arg_nb(char *str, int nb, size_t bytes)
{
    char temp[strlen(str) + 1] = {};
    int i = 0;
    char *token = NULL;
    char *save = temp;
    char *final = NULL;

    memset(temp, 0, strlen(str) + 1);
    strncpy(temp, str, strlen(str));
    i = 0;
    token = strtok_r(temp, " ", &save);
    // i - 1 is absolutely necessary because we're taking from
    // saveptr which points to the next token.
    while (i < nb - 1 && token != NULL) {
        token = strtok_r(NULL, " ", &save);
        i++;
    }
    final = strndup(save, bytes);
    return final;
}
