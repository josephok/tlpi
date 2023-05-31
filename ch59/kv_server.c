#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "sockets/inet_sockets.h"
#include "kv.h"
#include "hashtable.h"

int main(int argc, char const *argv[])
{
    socklen_t addrlen;
    struct sockaddr_storage claddr;
    int cfd;
    char addrStr[ADDRSTRLEN];
    char *command_arr[COMMAND_ARR_LEN];

    // [SET, DEL, GET]
    command_arr[0] = (char *)malloc(COMMAND_TOKEN_LEN + 1);
    command_arr[1] = (char *)malloc(KV_LEN + 1);
    command_arr[2] = (char *)malloc(KV_LEN + 1);

    int lfd = inetListen(PORT_NUMBER, 5, &addrlen);
    char command_str[CMD_LEN];
    if (lfd == -1)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    HashTable *table = create_table(CAPACITY);

    for (;;)
    {
        addrlen = sizeof(struct sockaddr_storage);
        cfd = accept(lfd, (struct sockaddr *)&claddr, &addrlen);
        if (cfd == -1)
        {
            perror("accept");
            continue;
        }

        inetAddressStr((struct sockaddr *)&claddr, addrlen, addrStr, ADDRSTRLEN - 1);
        printf("Connection from %s\n", addrStr);

        FILE *file = fdopen(cfd, "r");

        for (;;)
        {
            memset(command_str, '\0', CMD_LEN);
            memset(command_arr[1], '\0', KV_LEN + 1);
            memset(command_arr[2], '\0', KV_LEN + 1);
            char *s = fgets(command_str, CMD_LEN, file);
            if (s == NULL)
            {
                close(cfd);
                break;
            }

            trimTrailing(command_str);
            parse_cmd(command_str, command_arr);

            printf("Get command from client: %s %s %s\n", command_arr[0], command_arr[1], command_arr[2]);
            if (is_set(command_arr[0]))
            {
                printf("set key: %s with value: %s\n", command_arr[1], command_arr[2]);
                ht_insert(table, command_arr[1], command_arr[2]);
                write(cfd, "OK\n", 4);
            }
            else if (is_get(command_arr[0]))
            {
                char *value = ht_search(table, command_arr[1]);
                if (value != NULL)
                {
                    printf("get key: %s with value: %s\n", command_arr[1], value);
                    write(cfd, value, strlen(value) + 1);
                    write(cfd, "\n", 2);
                }
                else
                {
                    write(cfd, "NULL\n", 6);
                }
            }
            else if (is_del(command_arr[0]))
            {
                printf("del key: %s\n", command_arr[1]);
                ht_delete(table, command_arr[1]);
                write(cfd, "OK\n", 4);
            }
            else
            {
                printf("UNKNOWN COMMAND\n");
            }
        }
    }

    return 0;
}
