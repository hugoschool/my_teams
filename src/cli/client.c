#include "client/client.h"
#include "client/args.h"
#include "common.h"
#include "logging_client.h"
#include "server/events.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>

static void init_sub_teams(client_t *client)
{
    client->subscribed_teams = malloc(sizeof(sub_teams_t));
    client->subscribed_teams->amount = 1;
    client->subscribed_teams->team_index = 0;
    client->subscribed_teams->team_uuid = calloc(client->subscribed_teams->amount, sizeof(char *));
    client->subscribed_teams->team_uuid[0] = NULL;
}

int client_loop(client_t *client)
{
    char *cmd_line = NULL;
    struct pollfd pfds[2];
    size_t len = 0;
    int bytes = 0;

    // TODO: signalfd
    pfds[0].fd = client->socket_fd;
    pfds[0].events = POLLIN;
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;
    while (1) {
        if (poll(pfds, 2, 0) == -1) {
            perror("poll");
            break;
        }
        if (pfds[0].revents & POLLIN) {
            int verify = recv(client->socket_fd, client->buffer, BIG_BUFFER_SIZE, 0);
            if (verify == 0) {
                printf("Server closed its connexion.\n");
                break;
            }
            handle_server_events(client);
            memset(client->buffer, '\0', BIG_BUFFER_SIZE);
        }
        if (pfds[1].revents & POLLIN) {
            bytes = getline(&cmd_line, &len, stdin);
            if (bytes == -1) {
                return -1;
            }
            command_parser(cmd_line, client);
            memset(client->buffer, '\0', BIG_BUFFER_SIZE);
            cmd_line = NULL;
        }
    }
    free(cmd_line);
    return 0;
}

bool teams_client(client_args_t *args)
{
    client_t client = {
        .socket_fd = -1,
        .logged = false,
        .uuid = "\0",
        .user_name = "\0",
        .context = {"\0", "\0", "\0", BASE},
        .buffer = {0},
        .subscribed_teams = NULL
    };

    struct sockaddr_in addr;

    init_sub_teams(&client);
    addr.sin_addr.s_addr = args->ip;
    addr.sin_port = htons(args->port);
    addr.sin_family = AF_INET;
    client.socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client.socket_fd == -1) {
        perror("socket");
        return false;
    }
    if (connect(client.socket_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(client.socket_fd);
        perror("connect");
        return false;
    }
    recv(client.socket_fd, client.buffer, BIG_BUFFER_SIZE, 0);
    memset(client.buffer, '\0', BIG_BUFFER_SIZE);
    printf("%s", client.buffer);
    client_loop(&client);
    return true;
}
