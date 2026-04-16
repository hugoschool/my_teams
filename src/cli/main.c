#include "client/args.h"
#include "client/client.h"
#include <stdio.h>

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
