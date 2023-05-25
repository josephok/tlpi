#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    fork();
    fork();
    fork();

    sigset_t empty_set;
    sigemptyset(&empty_set);
    sigsuspend(&empty_set);
    return 0;
}
