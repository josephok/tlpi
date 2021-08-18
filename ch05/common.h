#ifndef _COMMON_H
#define _COMMON_H

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <sys/uio.h>

#define OPEN_FLAGS_WRITE (O_CREAT | O_WRONLY | O_APPEND)
#define FILE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

#endif