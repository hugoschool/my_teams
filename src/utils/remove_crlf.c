/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** remove_crlf.c
*/

#include "common.h"
#include "utils.h"
#include <string.h>

void remove_crlf(char *str)
{
    size_t len = 0;

    if (strcmp_end(str, CRLF) != 0)
        return;
    len = strlen(str);
    str[len - 1] = 0;
    str[len - 2] = 0;
}
