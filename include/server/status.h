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

// Prefer to use the macro if you know by advance the value of your status.
const char *get_status(int code);

enum status_codes {
    _25120 = 25120,
    _200 = 200,
    _250 = 250,
    _251 = 251,
    _430 = 430,
    _435 = 435,
    _440 = 440,
    _450 = 450,
    _451 = 451,
    _460 = 460,
    _461 = 461,
    _462 = 462,
    _463 = 463,
    _464 = 464,
    _499 = 499,
    _500 = 500,
};

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
    const char *_461;
    const char *_462;
    const char *_463;
    const char *_464;
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
    ._461 = "461 Unknown team."CRLF,
    ._462 = "462 Unknown channel."CRLF,
    ._463 = "463 Unknown thread."CRLF,
    ._464 = "464 Unknown user."CRLF,
    ._499 = "499 Badly formed request."CRLF,
    ._500 = "500 Server failure."CRLF,
};

#endif
