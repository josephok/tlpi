/*
Rewrite the programs in Listing 57-3 (us_xfr_sv.c) and Listing 57-4 (us_xfr_cl.c) to use
the Linux-specific abstract socket namespace (Section 57.6).
*/

#include "us_xfr.h"
#define BACKLOG 5

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);

    /* Construct server socket address, bind socket to it, and make this a listening socket */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;

    strncpy(&addr.sun_path[1], "server", sizeof(addr.sun_path) - 1);
    if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
        perror("bind");
    if (listen(sfd, BACKLOG) == -1)
        perror("listen");
    for (;;)
    {   /* Handle client connections iteratively */
        /* Accept a connection. The connection is returned on a new socket, 'cfd'; the listening socket ('sfd') remains open and can be used to accept further connections. */
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
            perror("accept");
        /* Transfer data from connected socket to stdout until EOF */
        while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                perror("partial/failed write");
        if (numRead == -1)
            perror("read");

        if (close(cfd) == -1)
            perror("close");
    }
}