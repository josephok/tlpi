/* 5-4
Implement dup() and dup2() using fcntl() and, where necessary, close().
(You may ignore the fact that dup2() and fcntl() return different errno
values for some error cases.) For dup2(), remember to handle the special
case where oldfd equals newfd. In this case, you should check whether oldfd
is valid, which can be done by, for example, checking if fcntl(oldfd, F_GETFL) succeeds.
If oldfd is not valid, then the function should return –1 with errno set to EBADF. */

/* The dup2() system call makes a duplicate of the file descriptor given in oldfd
using the descriptor number supplied in newfd. If the file descriptor specified
in newfd is already open, dup2() closes it first. (Any error that occurs during
this close is silently ignored; safer programming practice is to explicitly
close() newfd if it is open before the call to dup2().)
We could simplify the preceding calls to close() and dup() to the following:
dup2(1, 2);
A successful dup2() call returns the number of the duplicate descriptor
(i.e., the value passed in newfd).
If oldfd is not a valid file descriptor, then dup2() fails with the error
EBADF and newfd is not closed. If oldfd is a valid file descriptor, and oldfd
and newfd have the same value, then dup2() does nothing—newfd is not closed,
and dup2() returns the newfd as its function result. */

#include "common.h"

int mydup2(int oldfd, int newfd)
{
    int status = fcntl(oldfd, F_GETFL);
    if (status == -1)
    {
        errno = EBADF;
        return -1;
    }

    if (oldfd == newfd)
    {
        return newfd;
    }

    close(newfd);
    return fcntl(oldfd, F_DUPFD, newfd);
}

int main(int argc, char const *argv[])
{
    assert(mydup2(0, 0) == 0);
    assert(mydup2(0, 1) == 1);
    assert(mydup2(0, 2) == 2);
    assert(mydup2(-1, 1) == -1);
    assert(errno == EBADF);
    return 0;
}
