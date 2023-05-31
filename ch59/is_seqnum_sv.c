#include <netdb.h>
#include "is_seqnum.h"
#include "sockets/inet_sockets.h"

#define BACKLOG 50

int main(int argc, char *argv[])
{
    uint32_t seqNum = 0;
    char reqLenStr[INT_LEN] = {'\0'};
    char seqNumStr[INT_LEN];
    struct sockaddr_storage claddr;
    int lfd, cfd, optval, reqLen;
    socklen_t addrlen;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    char addrStr[ADDRSTRLEN];
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    lfd = inetListen(PORT_NUM, BACKLOG, &addrlen);
    for (;;)
    {
        /* Handle clients iteratively */
        /* Accept a client connection, obtaining client's address */
        addrlen = sizeof(struct sockaddr_storage);
        cfd = accept(lfd, (struct sockaddr *)&claddr, &addrlen);
        if (cfd == -1)
        {
            perror("accept");
            continue;
        }

        inetAddressStr((struct sockaddr *)&claddr, addrlen, addrStr, ADDRSTRLEN - 1);
        printf("Connection from %s\n", addrStr);
        /* Read client request, send sequence number back */
        FILE *file = fdopen(cfd, "r");
        char *s = fgets(reqLenStr, INT_LEN, file);
        if (s == NULL)
        {
            close(cfd);
            continue;
        }

        /* Failed read; skip request */
        /* Watch for misbehaving clients */ /* Bad request; skip it */
        reqLen = atoi(reqLenStr);
        if (reqLen <= 0)
        {
            close(cfd);
            continue;
        }
        snprintf(seqNumStr, INT_LEN, "%d\n", seqNum);
        if (write(cfd, &seqNumStr, strlen(seqNumStr)) != strlen(seqNumStr))
            fprintf(stderr, "Error on write");
        seqNum += reqLen; /* Update sequence number */
        if (close(cfd) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
    }
}
