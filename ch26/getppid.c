/*
Write a program to verify that when a child’s parent terminates,
a call to getppid() returns 1 (the process ID of init).
*/

#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    switch (fork())
    {
    case -1:
        perror("fork error");
        _exit(-1);

    case 0:
        sleep(3);
        pid_t ppid = getppid();
        printf("ppid is %d\n", ppid);

    default:
        break;
    }
    return 0;
}
