/*
Suppose that we have three processes related as grandparent, parent, and child,
and that the grandparent doesn’t immediately perform a wait() after the parent exits,
so that the parent becomes a zombie. When do you expect the grandchild to be adopted
by init (so that getppid() in the grandchild returns 1):
after the parent terminates or after the grandparent does a wait()?
Write a program to verify your answer.
*/

/*
after the grandparent does a wait(), so that parent is not zombie anymore.
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    switch (fork())
    {
    case -1:
        perror("fork error");
        _exit(-1);

    case 0:
        switch (fork())
        {
        case -1:
            perror("fork error");
            _exit(-1);

        case 0:
            // child
            printf("I am child with pid: %d, and my parent is %d\n", getpid(), getppid());
            sleep(10);
            printf("I am child with pid: %d, and my parent is %d\n", getpid(), getppid());
            break;

        default:
            // parent
            printf("I am parent with pid: %d\n", getpid());
            break;
        }
        break;

    default:
        // grandparent
        printf("I am grandparent with pid: %d\n", getpid());
        sleep(5);
        wait(NULL);
        break;
    }
    return 0;
}
