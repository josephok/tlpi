// int sigaction(int signum, const struct sigaction *act,
//                      struct sigaction *oldact);
#include "abort.h"

void my_abort(void)
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGABRT);
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);

    raise(SIGABRT);
    struct sigaction sig_act = {
        .sa_handler = SIG_DFL};
    sigaction(SIGABRT, &sig_act, NULL);
    raise(SIGABRT);
}