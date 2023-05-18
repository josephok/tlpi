/* 20-4.
Implement siginterrupt() using sigaction().*/
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int my_siginterrupt(int sig, int flag)
{
    struct sigaction act = {
        .sa_handler = SIG_DFL,
        .sa_flags = 0
    };

    if (flag == 0)
    {
        act.sa_flags = SA_RESTART;
    }
    return sigaction(sig, &act, NULL);
}

int main(int argc, char const *argv[])
{
    int ret = my_siginterrupt(SIGUSR1, 0);
    printf("%d\n", ret);
    return 0;
}
