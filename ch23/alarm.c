#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

// unsigned int alarm(unsigned int seconds);

static unsigned int myalarm(unsigned int seconds)
{
    struct timeval it_interval = {
        .tv_sec = 0,
        .tv_usec = 0};

    struct timeval it_value = {
        .tv_sec = seconds,
        .tv_usec = 0};

    struct itimerval new_value = {
        .it_interval = it_interval,
        .it_value = it_value
    };
    return setitimer(ITIMER_REAL, &new_value, NULL);

}

int main()
{
    myalarm(5);
    sigset_t set;
    sigaddset(&set, SIGALRM);
    sigwaitinfo(&set, NULL);

}
