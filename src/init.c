#include "plib.h"

void hang()
{
    printf("Hanging...\n"); // display a message
    while (1); // while loop of death
}

void loop()
{
    while (1)
    {
        // execute our shell
        printf("Executing: /bin/psh\n");
        int status = execute("/bin/psh");
        if (status != 0)
        {
            printf("Failed. Returned %d", status);
            hang();
        }
    }
}

int main()
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    if(getpid() != 1) // we need pid 1
    {
        printf("Failed to run init under PID %d.\n",getpid());
        exit(0);
    }

    // display branding message
    printf("poop Init System\n");

    // mount dev, sys and proc
    printf("Mounting sysfs\n");
    if (mount("none", "/sys", "sysfs", 0, "") != 0)
    {
        printf("Failed to mount sysfs.\n");
        hang();
    }

    printf("Mounting devtmpfs\n");
    if (mount("none", "/dev", "devtmpfs", 0, "") != 0)
    {
        printf("Failed to mount devtmpfs.\n");
        hang();
    }

    printf("Mounting proc\n");
    if (mount("none", "/proc", "proc", 0, "") != 0)
    {
        printf("Failed to mount proc.\n");
        hang();
    }

    // set printk to the second level
    int printk = open("/proc/sys/kernel/printk", O_WRONLY | O_APPEND); // append, write only
    char buffer[] = {'2'};
    write(printk, buffer, 1); // write the buffer to /proc/sys/kernel/printk

    loop(); // do the init loop
    return 0;
}