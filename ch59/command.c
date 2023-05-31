#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void parse_cmd(char *command_str, char **command_arr)
{
    char *token = strtok(command_str, " ");
    if (token == NULL)
    {
        return;
    }

    strncpy(command_arr[0], token, strlen(token));

    token = strtok(NULL, " ");
    if (token == NULL)
    {
        return;
    }
    strncpy(command_arr[1], token, strlen(token));

    token = strtok(NULL, " ");
    if (token == NULL)
    {
        return;
    }
    strncpy(command_arr[2], token, strlen(token));
}

void trimTrailing(char *str)
{
    int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
        {
            index = i;
        }

        i++;
    }

    /* Mark next character to last non-white space character as NULL */
    str[index + 1] = '\0';
}

bool is_set(const char *str)
{
    return (toupper(str[0]) == 'S' && toupper(str[1]) == 'E' && toupper(str[2]) == 'T');
}

bool is_get(const char *str)
{
    return (toupper(str[0]) == 'G' && toupper(str[1]) == 'E' && toupper(str[2]) == 'T');
}

bool is_del(const char *str)
{
    return (toupper(str[0]) == 'D' && toupper(str[1]) == 'E' && toupper(str[2]) == 'L');
}
