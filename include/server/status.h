/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** status.h
*/

#ifndef STATUS_H_
    #define STATUS_H_

    #include "common.h"
    #include <string.h> // IWYU pragma: keep
    #include <unistd.h>

    #define GET_STATUS(c) status._##c
    #define WRITE_STATUS(fd, c) write(fd, status._##c, strlen(status._##c))

typedef struct {
    const char *_25120;
} status_codes_t;

static const status_codes_t status = {
    ._25120 = "25120 MAICHE Protocol initialized."CRLF,
};

#endif
