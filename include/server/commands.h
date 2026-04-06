/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "server.h"
    #include <unistd.h>

typedef struct {
    const char *command;
    void (*function)(server_t *server);
    // Represents the amount of arguments the command can take.
    // Ex: USER a takes in 1 argument
    const unsigned int args_amount;
    // Needs for user to be logged in
    bool needs_auth;
} commands_t;

void command_login(server_t *server);
void command_logout(server_t *server);
void command_users(server_t *server);
void command_user(server_t *server);
void command_message_send(server_t *server);
void command_messages(server_t *server);
void command_create_team(server_t *server);
void command_teams(server_t *server);
void command_team(server_t *server);
void command_subscribe_team(server_t *server);
void command_unsubscribe_team(server_t *server);
void command_subscribed(server_t *server);
void command_list_subscribed_users(server_t *server);
void command_create_channel(server_t *server);

static const commands_t cmds[] = {
    {
        .command = "LOGIN",
        .function = &command_login,
        .args_amount = 1,
        .needs_auth = false
    },
    {
        .command = "LOGOUT",
        .function = &command_logout,
        .args_amount = 0,
        .needs_auth = true
    },
    {
        .command = "USERS",
        .function = &command_users,
        .args_amount = 0,
        .needs_auth = true
    },
    {
        .command = "USER",
        .function = &command_user,
        .args_amount = 1,
        .needs_auth = true
    },
    {
        .command = "MESSAGE_SEND",
        .function = &command_message_send,
        .args_amount = 2,
        .needs_auth = true
    },
    {
        .command = "MESSAGES",
        .function = &command_messages,
        .args_amount = 1,
        .needs_auth = true
    },
    {
        .command = "CREATE_TEAM",
        .function = &command_create_team,
        .args_amount = 2,
        .needs_auth = true
    },
    {
        .command = "TEAMS",
        .function = &command_teams,
        .args_amount = 0,
        .needs_auth = true
    },
    {
        .command = "TEAM",
        .function = &command_team,
        .args_amount = 1,
        .needs_auth = true
    },
    {
        .command = "SUBSCRIBE_TEAM",
        .function = &command_subscribe_team,
        .args_amount = 1,
        .needs_auth = true
    },
    {
        .command = "UNSUBSCRIBE_TEAM",
        .function = &command_unsubscribe_team,
        .args_amount = 1,
        .needs_auth = true
    },
    {
        .command = "SUBSCRIBED",
        .function = &command_subscribed,
        .args_amount = 0,
        .needs_auth = true
    },
    {
        .command = "LIST_SUBSCRIBED_USERS",
        .function = &command_list_subscribed_users,
        .args_amount = 1,
        .needs_auth = true
    },
    {
        .command = "CREATE_CHANNEL",
        .function = &command_create_channel,
        .args_amount = 3,
        .needs_auth = true
    },
    {.command = NULL, .function = NULL, .args_amount = 0, .needs_auth = false}
};

void commands_handler(server_t *server);

#endif
