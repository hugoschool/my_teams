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
    {.command = NULL, .function = NULL, .args_amount = 0, .needs_auth = false}
};

void commands_handler(server_t *server);

#endif
