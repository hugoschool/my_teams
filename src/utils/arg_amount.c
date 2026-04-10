/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** arg_amount.c
*/

#include <string.h>
#include <stdio.h>

size_t arg_amount(char *str)
{
    char temp[strlen(str) + 1] = {};
    size_t i = 0;
    char *token = NULL;

    memset(temp, 0, strlen(str) + 1);
    strncpy(temp, str, strlen(str));
    token = strtok(temp, " ");
    while (token != NULL) {
        token = strtok(NULL, " ");
        i++;
    }
    return i;
}

size_t arg_amount_quote(char *str)
{
    char temp[strlen(str) + 1] = {};
    size_t i = 0;
    char *token = NULL;

    memset(temp, 0, strlen(str) + 1);
    strncpy(temp, str, strlen(str));
    token = strtok(temp, "\"");
    while (token != NULL) {
        token = strtok(NULL, "\"");
        i++;
    }
    return i;
}
