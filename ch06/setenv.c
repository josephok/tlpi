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

int my_setenv(const char *name, const char *value, bool overwrite)
{
    bool exists = false;
    if (getenv(name) != NULL)
    {
        exists = true;
    }

    if (!exists || overwrite)
    {
        size_t len = strlen(name) + strlen(value) + 2;
        char *new_env = malloc(len);
        snprintf(new_env, len, "%s=%s", name, value);
        return putenv(new_env);
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    my_setenv("NAME", "joe", true);
    char *name = getenv("NAME");
    printf("NAME: %s\n", name);

    my_setenv("NAME", "joe1", true);
    name = getenv("NAME");
    printf("NAME: %s\n", name);
    return 0;
}
