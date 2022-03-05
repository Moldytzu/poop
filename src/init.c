#include <stdio.h>
#include <stdlib.h>
#include "plib.h"

void hang()
{
    printf("Hanging...\n"); // display a message
    while(1); // while loop of death
}

int main()
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("poop Init System\n");

    // execute our shell
    printf("Executing: /bin/psh\n");
    int status = execute("/bin/psh");
    if(status != 0)
    {
        printf("Failed. Returned %d",status);
    }
    
    hang();
    return 0;
}