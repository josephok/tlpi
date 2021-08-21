#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int ch;
    char *file_name = argv[argc - 1];
    size_t n = 10;
    bool use_default_n = true;
    while ((ch = getopt(argc, argv, "n:")) != -1)
    {
        switch (ch)
        {
        case 'n':
            n = atoi(optarg);
            use_default_n = false;
            break;
        default:
            printf("Invalid option\n");
            exit(EXIT_FAILURE);
        }
    }

    if (use_default_n && argc != 2)
    {
        printf("Usage: %s [ –n num ] file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!use_default_n && argc != 4)
    {
        printf("Usage: %s [ –n num ] file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        perror("File open error");
        return EXIT_FAILURE;
    }

    char buffer[BUF_SIZE];
    size_t nread;
    size_t line = 0;
    while ((nread = fread(buffer, 1, BUF_SIZE, f)) > 0)
    {
        for (size_t i = 0; i < nread; i++)
        {
            if (buffer[i] == '\n')
            {
                line++;
            }
        }
    }

    int start_line = line - n;
    fseek(f, 0, SEEK_SET);
    int j = 0;
    int k = 0;
    while ((nread = fread(buffer, 1, 1, f)) > 0)
    {
        k++;
        if (buffer[0] == '\n')
        {
            j++;
        }
        if (j == start_line)
        {
            break;
        }
    }
    fseek(f, k, SEEK_SET);
    while ((nread = fread(buffer, 1, BUF_SIZE - 1, f)) > 0)
    {
        buffer[nread] = '\0';
        printf("%s", buffer);
    }
    return 0;
}
