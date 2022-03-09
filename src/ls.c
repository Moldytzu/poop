#include "plib.h"

int main(int argc, char **argv)
{
    // disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    argv++; // skip the file path

    // append . if no path is supplied
    if (!*argv)
        *--argv = (char *)".";

    // loop thru argv
    while (*argv)
    {
        if (isempty(*argv)) continue; // skip empty
        DIR *d = opendir(*argv); // open directory
        if (d)
        {
            struct dirent *dir;
            while ((dir = readdir(d)) != NULL) // read files from directory
            {
                printf("%s ", dir->d_name); // print the name
            }
            closedir(d); // close directory
        }
        else
        {
            printf("Unknown directory %s",*argv);
        }
        argv++; // increment address
    }

    // print newline
    printf("\n");
}