#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/signalfd.h>

int create_signalfd(void)
{
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
        return -1;
    return signalfd(-1, &mask, 0);
}

void signalfd_handler(bool *running)
{
    *running = false;
}
