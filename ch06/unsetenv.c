/* 6-3
Implement setenv() and unsetenv() using getenv(), putenv(), and,
where necessary, code that directly modifies environ. Your version
of unsetenv() should check to see whether there are multiple definitions
of an environment variable, and remove them all (which is what the glibc
version of unsetenv() does). */

// int setenv(const char *name, const char *value, int overwrite);
// int unsetenv(const char *name);
#include "common.h"

// char *getenv(const char *name);
// int putenv(char *string);

int my_unsetenv(const char *name)
{
    bool exists = (getenv(name) != NULL);
    if (!exists)
    {
        return 0;
    }
    return putenv(name);
}

int main(int argc, char const *argv[])
{
    setenv("NAME", "joe", true);
    char *name = getenv("NAME");
    printf("NAME: %s\n", name);

    my_unsetenv("NAME");
    name = getenv("NAME");
    printf("NAME: %s\n", name);
    return 0;
}
