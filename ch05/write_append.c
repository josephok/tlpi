/* 5-2
Write a program that opens an existing file for writing with the O_APPEND flag,
and then seeks to the beginning of the file before writing some data.
Where does the data appear in the file? Why? */

// It will write to end of file, because O_APPEND flags ensure that each write
// happens at end of file

#include "common.h"

int main(int argc, char const *argv[])
{
    int fd = open("1.txt", OPEN_FLAGS_WRITE, FILE_PERMS);
    lseek(fd, 0, SEEK_SET);
    write(fd, "abc", 3);

    lseek(fd, 0, SEEK_SET);
    write(fd, "abc", 3);

    lseek(fd, 0, SEEK_SET);
    write(fd, "abc", 3);

    lseek(fd, 0, SEEK_SET);
    write(fd, "abc", 3);

    close(fd);
    return 0;
}
