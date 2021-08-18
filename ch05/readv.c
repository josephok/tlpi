/* 5-7
Implement readv() and writev() using read(), write(),
and suitable functions from the malloc package (Section 7.1.2). */

// ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
// ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#include "common.h"
#define IOV_SISE 3
#define IOV_LENGTH 4

ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt)
{
    ssize_t nread = 0;
    for (size_t i = 0; i < iovcnt; i++)
    {
        ssize_t n = read(fd, (iov + i)->iov_base, (iov + i)->iov_len);
        if (n == -1)
        {
            return -1;
        }

        if (n > 0)
        {
            nread += n;
        }
    }

    return nread;
}

int main(int argc, char const *argv[])
{
    int fd = open("1.txt", O_RDONLY);
    struct iovec iov[IOV_SISE];
    for (size_t i = 0; i < IOV_SISE; i++)
    {
        iov[i].iov_base = malloc(IOV_LENGTH);
        iov[i].iov_len = IOV_LENGTH;
    }
    ssize_t nread = my_readv(fd, iov, IOV_SISE);
    if (nread < 0)
    {
        perror("write error!");
    }

    printf("%ld bytes read\n", nread);

    for (size_t i = 0; i < IOV_SISE; i++)
    {
        free(iov[i].iov_base);
    }
    close(fd);
    return 0;
}
