/* 20-2.
Write a program that shows that when the disposition of a pending
signal is changed to be SIG_IGN, the program never sees (catches) the signal. */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    raise(SIGUSR1);

    sigdelset(&sigset, SIGUSR1);
    struct sigaction act = {
        .sa_handler = SIG_IGN,
        .sa_mask = sigset};
    sigaction(SIGUSR1, &act, NULL);

    // This will pause until one signal come, since we can't see SIGUSR1 signal
    pause();

    return 0;
}
