#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "stdio.h"
#include "utils.h"
#include <stdlib.h>


ssize_t receive(client_t *client, size_t bytes_to_recv)
{
    size_t original_bytes_to_recv = bytes_to_recv;
    size_t index = 0;

    while (bytes_to_recv > 0) {
        ssize_t bytes_recv = recv(client->socket_fd, &client->buffer[index], BIG_BUFFER_SIZE, 0);
        if (bytes_recv <= 0) {
            return bytes_recv;
        }
        bytes_to_recv -= bytes_recv;
        index += bytes_recv;
    }
    return original_bytes_to_recv;
}
