#include <unistd.h>
#include <stdint.h>

uint32_t execute(const char *path)
{
    return execv(path, NULL);
}