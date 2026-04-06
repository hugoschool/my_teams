
#ifndef TEAMS_CLIENT_COMMANDS_H_
    #define TEAMS_CLIENT_COMMANDS_H_

    #include <unistd.h>
    #include "client/client.h"

    void cmd_login(char *command, client_t * client);

    typedef struct command_s {
        const char *cmd;
        unsigned int nb_args;
        void (*func)(char *, client_t *);
    } command_t;

    const command_t commands[] = {
        {"/help", 0, NULL},
        {"/login", 1, &cmd_login},
        {"/logout", 0, NULL},
        {"/users", 0, NULL},
        {"/user", 1, NULL},
        {"/send", 2, NULL},
        {"/messages", 1, NULL},
        {"/subscribe", 1, NULL},
        {"/subscribed", 1, NULL},
        {"/unsubscribe", 1, NULL},
        {"/use", 3, NULL},
        {"/create", 0, NULL},
        {"/list", 0, NULL},
        {"/info", 0, NULL},
        {NULL, 0, NULL}
    };

#endif
