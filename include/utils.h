/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** utils.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include <stdbool.h>
    #include <stddef.h>

int strcmp_start(const char *str, const char *start);
int strcmp_end(const char *str, const char *end);
void remove_crlf(char *str);
size_t strccount(const char *str, char c);
char *get_arg(char *str, int nb);
char *get_arg_quote(char *str, int nb);
size_t arg_amount(char *str);
int arg_amount_quote(char *str);
char *read_bytes_starting_arg(char *str, int nb, size_t bytes);
char *capitalize_cmd(char *cmd);
int limit_nb(int nb, int max);
void super_free(int nb, ...);
int create_signalfd(void);
void signalfd_handler(bool *running);

#endif
