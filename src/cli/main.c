#include "client/args.h"
#include "client/client.h"
#include <stdio.h>

// client->data_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (client->data_socket == -1)
//         return;
//     if (connect(client->data_socket, (struct sockaddr *)sd,
//             sizeof(*sd)) == -1) {
//         write(fd, S_421, strlen(S_421));
//         return;
//     }
//     write(fd, STATUS_200, strlen(STATUS_200));
//     client->mode = ACTIVE;

int main(int argc, char **argv)
{
    client_args_t args = parse_args(argc, argv);

    if (args.valid == false) {
        fprintf(stdout, "Invalid arguments\n");
        return 84;
    }
    if (args.help)
        return 0;
    if (!teams_client(&args))
        return 84;
    return 0;
}
