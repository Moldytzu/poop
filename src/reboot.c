#include <unistd.h>
#include <sys/reboot.h>

int main()
{
    sync();              // sync filesystems
    reboot(RB_AUTOBOOT); // do reboot
    return 0;
}