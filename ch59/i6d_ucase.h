#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 10 /* Maximum size of messages exchanged between client and server */
#define PORT_NUM 50002 /* Server port number */