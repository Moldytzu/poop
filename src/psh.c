#include <stdio.h>

int main()
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);
    
    printf("psh");
    return 0;
}