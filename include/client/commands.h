
#ifndef TEAMS_CLIENT_COMMANDS_H_
    #define TEAMS_CLIENT_COMMANDS_H_

    #include <unistd.h>
    #include "client/client.h"

    #define SEND "MESSAGE_SEND"
    #define SUBSCRIBE_TEAM "SUBSCRIBE_TEAM"
    #define UNSUBSCRIBE_TEAM "UNSUBSCRIBE_TEAM"
    #define SUBSCRIBED_LIST "LIST_SUBSCRIBED_USERS"

    #define TEAM_INFO "TEAM"
    #define CHANNEL_INFO "CHANNEL"
    #define THREAD_INFO "THREAD"

    #define CREATE_TEAM "CREATE_TEAM"
    #define CREATE_CHANNEL "CREATE_CHANNEL"
    #define CREATE_THREAD "CREATE_THREAD"
    #define CREATE_COMMENT "CREATE_COMMENT"

    #define TEAM_LIST "TEAMS"
    #define CHANNEL_LIST "CHANNELS"
    #define THREAD_LIST "THREADS"
    #define COMMENT_LIST "COMMENTS"

    #define NO_CONTEXT "NO_CONTEXT"

    void cmd_help(char *command, client_t * client);
    void cmd_login(char *command, client_t * client);
    void cmd_logout(char *command, client_t * client);
    void cmd_users(char *command, client_t * client);
    void cmd_user(char *command, client_t * client);
    void cmd_send(char *command, client_t * client);
    void cmd_messages(char *command, client_t * client);
    void cmd_subscribe(char *command, client_t *client);
    void cmd_subscribed(char *command, client_t *client);
    void cmd_unsubscribe(char *command, client_t *client);
    void cmd_use(char *command, client_t * client);
    void cmd_create(char *command, client_t * client);
    void cmd_list(char *command, client_t * client);
    void cmd_info(char *command, client_t * client);

    enum context_e define_context(client_t *client);
    void print_unknown_error(enum context_e context, client_t *client);

    enum context_e {
        BASE,
        TEAM,
        CHANNEL,
        THREAD,
    };

    typedef struct command_s {
        const char *cmd;
        unsigned int nb_args;
        void (*func)(char *, client_t *);
    } command_t;

    static const command_t commands[] = {
        {"/help", 0, &cmd_help},
        {"/login", 1, &cmd_login},
        {"/logout", 0, &cmd_logout},
        {"/users", 0, &cmd_users},
        {"/user", 1, &cmd_user},
        {"/send", 2, &cmd_send},
        {"/messages", 1, &cmd_messages},
        {"/subscribe", 1, &cmd_subscribe},
        {"/subscribed", 0, &cmd_subscribed},
        {"/unsubscribe", 1, &cmd_unsubscribe},
        {"/use", 0, &cmd_use},
        {"/create", 2, &cmd_create},
        {"/list", 0, &cmd_list},
        {"/info", 0, &cmd_info},
        {NULL, 0, NULL}
    };

#endif
