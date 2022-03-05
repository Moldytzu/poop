#include <unistd.h>
#include <sys/reboot.h>
#include <linux/reboot.h>

int main()
{
    sync();                             // sync filesystems
    reboot(LINUX_REBOOT_CMD_POWER_OFF); // do shutdown
    return 0;
}