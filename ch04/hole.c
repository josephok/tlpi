#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
    char random_garbage[1024]; /* Don't even bother to initialize */
    int fd = -1;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("Can't open file: ");
        return 2;
    }
    write(fd, random_garbage, 1024);
    lseek(fd, 5 * 4096, SEEK_CUR);
    write(fd, random_garbage, 1024);
    close(fd);
    return 0;
}