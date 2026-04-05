#include "client/client.h"
#include "client/args.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int client_loop(client_t *client)
{
    char *cmd_line = NULL;
    size_t len = 0;
    int bytes = 0;

    while (1) {
        memset(client->buffer, '\0', 4096);
        bytes = getline(&cmd_line, &len, stdin);
        if (bytes == -1) {
            return -1;
        }
        command_parser(cmd_line, client);
    }
    return 0;
}

int client_loop(client_t *client)
{

}

bool teams_client(client_args_t *args)
{
    client_t client = {.socket_fd = -1, .logged = false, .user_name = NULL, .uuid = "\0", .context = {"\0", "\0", "\0"}};

    client.sockaddr.sin_addr.s_addr = args->ip;
    client.sockaddr.sin_port = htons(args->port);
    client.sockaddr.sin_family = AF_INET;
    client.socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client.socket_fd == -1) {
        perror("socket");
        return false;
    }
    if (connect(client.socket_fd, (struct sockaddr *)&client.sockaddr, sizeof(client.sockaddr)) == -1) {
        close(client.socket_fd);
        perror("connect");
        return false;
    }
    memset(client.buffer, '\0', 4096);
    recv(client.socket_fd, client.buffer, 4096, 0);
    printf("%s", client.buffer);
    client_loop(&client);
    return true;
}
