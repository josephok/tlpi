#include <stdlib.h>
#include <stdio.h>

static void atexitFunc1(void)
{
    /* Get on_exit() declaration from <stdlib.h> */
    printf("atexit function 1 called\n");
}

int main(int argc, char const *argv[])
{
    atexit(atexitFunc1);
    /* code */
    return 0;
}