/* 5-7
Implement readv() and writev() using read(), write(),
and suitable functions from the malloc package (Section 7.1.2). */

// ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
// ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#include "common.h"
#define IOV_SISE 3
#define IOV_LENGTH 4

ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt)
{
    ssize_t nwrite = 0;
    for (size_t i = 0; i < iovcnt; i++)
    {
        ssize_t n = write(fd, (iov + i)->iov_base, (iov + i)->iov_len);
        if (n == -1)
        {
            return -1;
        }

        if (n > 0)
        {
            nwrite += n;
        }
    }

    return nwrite;
}

int main(int argc, char const *argv[])
{
    int fd = open("2.txt", O_CREAT | O_WRONLY | O_TRUNC, FILE_PERMS);
    struct iovec iov[IOV_SISE] = {
        {.iov_base = "1234", .iov_len = IOV_LENGTH},
        {.iov_base = "5678", .iov_len = IOV_LENGTH},
        {.iov_base = "9090", .iov_len = IOV_LENGTH}};

    ssize_t nread = my_writev(fd, iov, IOV_SISE);
    if (nread < 0)
    {
        perror("write error!");
    }

    printf("%ld bytes write\n", nread);

    close(fd);
    return 0;
}
