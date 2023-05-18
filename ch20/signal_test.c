/* signal test */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void handler(int signum)
{
    printf("caught signal: %d %s\n", signum, strsignal(signum));
}

int main(int argc, char const *argv[])
{
    struct sigaction act = {
        .sa_handler = handler,
        .sa_mask = 0};
    sigaction(SIGUSR1, &act, NULL);

    while (1)
    {
        printf("main ...\n");
        sleep(3);
    }

    return 0;
}
