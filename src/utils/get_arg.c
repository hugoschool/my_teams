/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** get_arg.c
*/

#include <string.h>
#include <stdio.h>

char *get_arg(char *str, int nb)
{
    char temp[strlen(str) + 1] = {};
    int i = 0;
    char *token = NULL;

    memset(temp, 0, strlen(str) + 1);
    strncpy(temp, str, strlen(str));
    i = 0;
    token = strtok(temp, " ");
    if (nb == 0)
        return strdup(token);
    while (i < nb && token != NULL) {
        token = strtok(NULL, " ");
        i++;
    }
    if (token == NULL)
        return NULL;
    return strdup(token);
}
