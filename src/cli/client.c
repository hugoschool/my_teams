#include "client/client.h"
#include "client/args.h"
#include <stdbool.h>
#include <stdio.h>

int client_loop(client_t *client)
{

}

bool teams_client(client_args_t *args)
{
    client_t client = {.socket_fd = -1, .logged = false, .user_name = NULL, .uuid = NULL, .context = {NULL, NULL, NULL}};

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
    char buff[4096];
    recv(client.socket_fd, buff, 4096, 0);
    printf("%s", buff);
    send(client.socket_fd, "LOGIN doug\r\n", 12, 0);
    recv(client.socket_fd, buff, 4096, 0);
    printf("%s", buff);
    return true;
}
