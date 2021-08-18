/* 4-1
The tee command reads its standard input until end-of-file,
writing a copy of the input to standard output and to the file named in its command-line argument.
(We show an example of the use of this command when we discuss FIFOs in Section 44.7.)
Implement tee using I/O system calls. By default, tee overwrites any existing file with the given name.
Implement the –a command-line option (tee –a file), which causes tee to append text to the end of
a file if it already exists. (Refer to Appendix B for a description of the getopt() function,
which can be used to parse command-line options.)
*/
#include "common.h"

int main(int argc, char **argv)
{
    int ch;
    char *file_name = argv[1];
    bool append = false;
    char buf[BUF_SIZE];
    while ((ch = getopt(argc, argv, "a:")) != -1)
    {
        switch (ch)
        {
        case 'a':
            append = true;
            file_name = optarg;
            break;
        default:
            printf("Invalid option\n");
            exit(EXIT_FAILURE);
        }
    }

    int fd;
    if (append)
    {
        fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, FILE_PERMS);
    }
    else
    {
        fd = open(file_name, OPEN_FLAGS_WRITE, FILE_PERMS);
    }

    int nread;
    while ((nread = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        write(fd, buf, nread);
        write(STDOUT_FILENO, buf, nread);
    }

    close(fd);
    return 0;
}
