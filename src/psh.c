#include "plib.h"

int main()
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);
    
    while(1)
    {
        printf("psh >> "); // write prompt
        char buffer[256];
        printf("%d -> %s\n",readline(buffer,256),buffer);
    }
    return 0;
}