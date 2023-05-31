#include <netdb.h>
#include "is_seqnum.h"
#include "sockets/inet_sockets.h"

int main(int argc, char *argv[])
{
    char *reqLenStr;
    char seqNumStr[INT_LEN];
    int cfd;
    ssize_t numRead;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    /* Requested length of sequence */
    /* Start of granted sequence */
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        fprintf(stderr, "%s server-host [sequence-len]\n", argv[0]);

    cfd = inetConnect(argv[1], PORT_NUM, SOCK_STREAM);
    /* Send requested sequence length, with terminating newline */
    reqLenStr = (argc > 2) ? argv[2] : "1";
    if (write(cfd, reqLenStr, strlen(reqLenStr)) != strlen(reqLenStr))
        perror("Partial/failed write (reqLenStr)");
    if (write(cfd, "\n", 1) != 1)
        perror("Partial/failed write (newline)");

    FILE *file = fdopen(cfd, "r");
    char *s = fgets(seqNumStr, INT_LEN, file);
    if (s == NULL)
    {
        perror("read error from server");
        exit(EXIT_FAILURE);
    }

    printf("Sequence number: %s", seqNumStr);
    exit(EXIT_SUCCESS);
}
