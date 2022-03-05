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

    // display branding message
    printf("poop Init System\n");

    // mount dev, sys and proc
    printf("Mounting sysfs\n");
    if(mount("none","/sys","sysfs",0,"") != 0)
    {
        printf("Failed to mount sysfs.\n");
        hang();
    }

    printf("Mounting devtmpfs\n");
    if(mount("none","/dev","devtmpfs",0,"") != 0)
    {
        printf("Failed to mount devtmpfs.\n");
        hang();
    }

    printf("Mounting proc\n");
    if(mount("none","/proc","proc",0,"") != 0)
    {
        printf("Failed to mount proc.\n");
        hang();
    }

    // execute our shell
    printf("Executing: /bin/psh\n");
    int status = execute("/bin/psh");
    if(status != 0)
    {
        printf("Failed. Returned %d",status);
        hang();
    }
    
    hang();
    return 0;
}