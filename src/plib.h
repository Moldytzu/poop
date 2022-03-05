#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>

static unsigned long console = 0; // console file descriptor

static int isempty(const char *s)
{
  while (*s) {
    if (!isspace(*s))
      return 0;
    s++;
  }
  return 1;
}

static int executea(const char *path, char *argv[])
{
    int pid;
    switch(pid = vfork()) // spawn child
    {
        case 0: // child
        {
            execv(path,argv); // execute
            break;
        }
        default: break; // do nothing
    }

    int status;
    waitpid(pid, &status, 0); // wait for pid to quit 
    return status;
}

static int execute(const char *path)
{
    char *argv[] = {(char*)path, NULL};
    return executea(path,argv); // wrap the argv
}

static char readchar()
{
    char c = 0;
    if(console == 0) open("/dev/console", O_RDWR | O_NDELAY); // open console
    while(!read(console,&c,1)); // wait for a byte
    return c; // return character
}

static int readline(char *buff, int len)
{   
    for (int i = 0; i<len;i++)
    {
        char c = readchar(); // read char

        switch (c)
        {
            case 0: // skip
                i--;
                break;
            case '\n': // terminate string and return the index
                buff[i] = 0;
                return i;
            default:
                buff[i] = c; // append the char
                break;
        }

    }
    buff[len-1] = 0; // terminate string
    return len; // return max len
}