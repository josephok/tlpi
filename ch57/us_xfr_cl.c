/*
Rewrite the programs in Listing 57-3 (us_xfr_sv.c) and Listing 57-4 (us_xfr_cl.c) to use
the Linux-specific abstract socket namespace (Section 57.6).
*/

#include "us_xfr.h"

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;
    uint8_t x;
    char buf[BUF_SIZE];
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        /* Create client socket */
        perror("socket");
    /* Construct server address, and make the connection */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;

    strncpy(&addr.sun_path[1], "server", sizeof(addr.sun_path) - 1);
    if (connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
        perror("connect");
    /* Copy stdin to socket */
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if (write(sfd, buf, numRead) != numRead)
            perror("partial/failed write");
    if (numRead == -1)
        perror("read");
    exit(EXIT_SUCCESS); /* Closes our socket; server sees EOF */
}