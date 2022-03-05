#include <stdio.h>
#include "plib.h"

int main()
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("poop init system\n");

    // execute our shell
    printf("executing: /bin/psh\n");
    execute("/bin/psh");

    while(1);
    return 0;
}