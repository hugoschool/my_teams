
#ifndef TEAMS_CLIENT_COMMANDS_H_
    #define TEAMS_CLIENT_COMMANDS_H_

    #include <unistd.h>
    #include "client/client.h"

    #define SEND "MESSAGE_SEND"

    void cmd_login(char *command, client_t * client);
    void cmd_logout(char *command, client_t * client);
    void cmd_users(char *command, client_t * client);
    // void cmd_send(char *command, client_t * client);
    void cmd_user(char *command, client_t * client);

    typedef struct command_s {
        const char *cmd;
        unsigned int nb_args;
        void (*func)(char *, client_t *);
    } command_t;

    const command_t commands[] = {
        {"/help", 0, NULL},
        {"/login", 1, &cmd_login},
        {"/logout", 0, &cmd_logout},
        {"/users", 0, &cmd_users},
        {"/user", 1, &cmd_user},
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
