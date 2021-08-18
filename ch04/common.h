#ifndef _COMMON_H
#define _COMMON_H

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OPEN_FLAGS_READ (O_RDONLY)
#define OPEN_FLAGS_WRITE (O_CREAT | O_WRONLY | O_TRUNC)
#define FILE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

#define BUF_SIZE 1024
#endif