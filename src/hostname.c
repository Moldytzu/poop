#include "plib.h"

int main(int argc, char *argv[])
{
    if(!argv[1]) // if we want to get it
    {
        char hostname[PATH_MAX];
        gethostname(hostname,sizeof(hostname)); // get it
        printf("%s\n", hostname); // display it
        exit(-1);
    }

    sethostname(argv[1],strlen(argv[1])); // set it
}