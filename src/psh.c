#include "plib.h"

int main()
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);
    
    while(1)
    {
        printf("psh >> "); // write prompt
        char buffer[256];
        readline(buffer,256); // read from the keyboard into the buffer

        if(strcmp(buffer,"exit") == 0)
            exit(0); // exit
        else
        {
            if(access(buffer,F_OK) != 0) // check if file exists
            {
                printf("Unknown command: %s\n", buffer);
                continue;
            }

            execute(buffer); // execute file
        }
    }
    return 0;
}