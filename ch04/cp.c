/* 4-2
Write a program like cp that, when used to copy a regular file that contains
holes(sequences of null bytes), also creates corresponding holes in the target
file.
*/

#include "common.h"

int main(int argc, char const *argv[])
{
    const char *src = argv[1];
    const char *dst = argv[2];
    char buf[BUF_SIZE];

    int fd1 = open(src, OPEN_FLAGS_READ);
    int fd2 = open(dst, OPEN_FLAGS_WRITE, FILE_PERMS);

    int nread;
    while ((nread = read(fd1, buf, BUF_SIZE)) > 0)
    {
        write(fd2, buf, nread);
    }

    close(fd1);
    close(fd2);
    return 0;
}
