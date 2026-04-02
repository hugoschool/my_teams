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
    const char *_200;
    const char *_250;
    const char *_251;
    const char *_430;
    const char *_435;
    const char *_440;
    const char *_450;
    const char *_451;
    const char *_460;
    const char *_499;
    const char *_500;
} status_codes_t;

static const status_codes_t status = {
    ._25120 = "25120 MAICHE Protocol initialized."CRLF,
    ._200 = "200 Success."CRLF,
    ._250 = "250 User logged in."CRLF,
    ._251 = "251 User logged out."CRLF,
    ._430 = "430 User already logged in."CRLF,
    ._435 = "435 User isn't logged in."CRLF,
    ._440 = "440 Already exists."CRLF,
    ._450 = "450 User already subscribed to this team."CRLF,
    ._451 = "451 User isn't subscribed to this team."CRLF,
    ._460 = "460 Given parameter is invalid."CRLF,
    ._499 = "499 Badly formed request."CRLF,
    ._500 = "500 Server failure."CRLF,
};

#endif
