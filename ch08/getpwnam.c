/* 8-2
Implement getpwnam() using setpwent(), getpwent(), and endpwent(). */

#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct passwd *my_getpwnam(const char *name)
{
    struct passwd *pw;
    while ((pw = getpwent()) != NULL)
    {
        if (strcmp(pw->pw_name, name) == 0)
        {
            return pw;
        }
    }

    setpwent();
    endpwent();
    return NULL;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s username\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct passwd *pw = my_getpwnam(argv[1]);
    if (pw == NULL)
    {
        printf("No user with username: %s found\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("username: %s, uid: %d, pw: %s\n", pw->pw_name, pw->pw_uid, pw->pw_passwd);
    return 0;
}
