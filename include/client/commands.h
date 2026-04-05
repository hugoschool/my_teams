
#ifndef TEAMS_CLIENT_COMMANDS_H_
    #define TEAMS_CLIENT_COMMANDS_H_

    typedef struct command_s {
        char *cmd;
        int nb_args;
    } command_t;

    const command_t commands[] = {
        {"/help", 0},
        {"/login", 1},
        {"/logout", 0},
        {"/users", 0},
        {"/user", 1},
        {"/send", 2},
        {"/messages", 1},
        {"/subscribe", 1},
        {"/subscribed", 1},
        {"/unsubscribe", 1},
        {"/use", 3},
        {"/create", 0},
        {"/list", 0},
        {"/info", 0}
    };

#endif
