#include "client/client.h"
#include "client/args.h"
#include <stdio.h>

bool teams_client(client_args_t *args)
{
    client_t client = {.socket_fd = -1};

    client.logged = false;
    client.uuid = NULL;
    client.sockaddr.sin_addr.s_addr = args->ip;
    client.sockaddr.sin_port = args->port;
    client.sockaddr.sin_family = AF_INET;

    client.socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client.socket_fd == -1)
        return false;
    if (connect(client.socket_fd, (struct sockaddr *)&client.sockaddr, sizeof(client.sockaddr)) == -1) {
        close(client.socket_fd);
        perror("connect");
        return false;
    }
    return true;
}
