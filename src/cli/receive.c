#include "client/client.h"
#include "client/commands.h"
#include "common.h"
#include "logging_client.h"
#include "stdio.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <sys/socket.h>

ssize_t receive(client_t *client, size_t bytes_to_recv)
{
    size_t original_bytes_to_recv = bytes_to_recv;
    size_t index = 0;
    struct pollfd pfd[1];

    pfd[0].fd = client->socket_fd;
    pfd[0].events = POLLIN;
    while (bytes_to_recv > 0) {
        if (poll(pfd, 1, 1) <= 0) {
            break;
        }
        if (pfd[0].revents & POLLIN) {
            ssize_t bytes_recv = recv(client->socket_fd, &client->buffer[index], BIG_BUFFER_SIZE, 0);
            if (bytes_recv <= 0 || errno == EAGAIN) {
                return bytes_recv;
            }
            bytes_to_recv -= bytes_recv;
            index += bytes_recv;
        }
    }
    return original_bytes_to_recv;
}
