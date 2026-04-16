#include "server/status.h"

// Behold, ugly shit
const char *get_status(int code)
{
    switch (code) {
        case _25120:    return GET_STATUS(25120);
        case _200:      return GET_STATUS(200);
        case _250:      return GET_STATUS(250);
        case _251:      return GET_STATUS(251);
        case _430:      return GET_STATUS(430);
        case _435:      return GET_STATUS(435);
        case _440:      return GET_STATUS(440);
        case _450:      return GET_STATUS(450);
        case _451:      return GET_STATUS(451);
        case _460:      return GET_STATUS(460);
        case _461:      return GET_STATUS(461);
        case _462:      return GET_STATUS(462);
        case _463:      return GET_STATUS(463);
        case _464:      return GET_STATUS(464);
        case _499:      return GET_STATUS(499);
        case _500:      return GET_STATUS(500);
        default:        return GET_STATUS(500);
    }
}
