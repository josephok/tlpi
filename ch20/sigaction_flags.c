/* 20-3.
Write programs that verify the effect of the SA_RESETHAND and
SA_NODEFER flags when establishing a signal handler with sigaction(). */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum)
{
    printf("caught signal\n");
    sleep(600);
}

/* Use kill -USR1 command will terminate the process immediately */
int main(int argc, char const *argv[])
{
    struct sigaction act = {
        .sa_handler = handler,
        .sa_flags = SA_RESETHAND | SA_NODEFER};
    sigaction(SIGUSR1, &act, NULL);
    // This one use disposition handler
    raise(SIGUSR1);
    return 0;
}
