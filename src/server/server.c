#include "server/args.h"
#include "server/server.h"
#include <stdio.h>
#include <stdlib.h>

static server_t *server_init(void)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL) {
        perror("malloc");
        return NULL;
    }
    server->poller = poller_init();
    if (server->poller == NULL) {
        free(server);
        return NULL;
    }
    return server;
}

bool teams_server(args_t *args)
{
    server_t *server = server_init();

    if (server == NULL)
        return false;

    return true;
}
