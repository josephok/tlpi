#include <stdlib.h>
#include <stdbool.h>

#define PORT_NUMBER "5000"
#define BACKLOG 5
#define CMD_LEN 4096
#define COMMAND_ARR_LEN 3
#define COMMAND_TOKEN_LEN 3
#define KV_LEN 1000

void parse_cmd(char *command_str, char **command_arr);
void trimTrailing(char *str);
bool is_set(const char* str);
bool is_get(const char* str);
bool is_del(const char* str);