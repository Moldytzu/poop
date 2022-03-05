#include "plib.h"

char **args(char *cmd)
{
    int spaces = 0, len = strlen(cmd);

    for (int i=0; i<len; i++) {
        if (cmd[i] == ' ') { // delimiter
            cmd[i] = 0; // split
            spaces++;
        }
    }

    char **argv = malloc(sizeof(char *) * ++spaces);
    
    int arg = 0;
    argv[arg++] = cmd;

    for (int i=0; i<len; i++) {
        if (!cmd[i])
            argv[arg++] = cmd + i + 1; // offset by i+1
    }

    argv[arg++] = 0; // terminate the array

    return argv;
}

int main()
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);
    
    while(1)
    {
        printf("psh >> "); // write prompt
        char buffer[256];
        readline(buffer,256); // read from the keyboard into the buffer

        if(isempty(buffer)) continue; // skip whitespace

        if(strcmp(buffer,"exit") == 0)
            exit(0); // exit
        else
        {
            char **argv = args(buffer);
            if(access(argv[0],F_OK) != 0) // check if file exists
            {
                printf("Unknown command: %s\n", buffer);
                continue;
            }

            executea(argv[0],argv); // execute file
        }
    }
    return 0;
}