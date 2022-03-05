#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int execute(const char *path)
{
    int pid;
    switch(pid = vfork()) // spawn child
    {
        case 0: // child
        {
            char *argv[] = {(char*)path, NULL};
            execv(path,argv); // execute
            break;
        }
        default: break; // do nothing
    }

    int status;
    waitpid(pid, &status, 0); // wait for pid to quit 
    return status;
}