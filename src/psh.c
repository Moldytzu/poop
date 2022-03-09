#include "plib.h"

int main()
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    while (1)
    {
        printf("psh >> "); // write prompt
        char buffer[256];
        readline(buffer, 256); // read from the keyboard into the buffer

        if (isempty(buffer))
            continue; // skip whitespace

        if (strcmp(buffer, "exit") == 0)
            exit(0); // exit
        else
        {
            char *pathenv = getenv("PATH"); // get path
            printf("%p\n\n",(void*)pathenv);
            const char **argv = split(buffer, ' '); // split at ' '
            if (executea(argv[0], (char **)argv, pathenv) == -69) // execute file
            {
                printf("Unknown command: %s\n", buffer);
                continue;
            }

            free(argv); // free argv
        }
    }
    return 0;
}