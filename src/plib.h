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
#include <dirent.h>

static const int isempty(const char *s)
{
    while (*s)
    {
        if (!isspace(*s))
            return 0;
        s++;
    }
    return 1;
}

static const char **split(char *str, char del)
{
    int spaces = 0, len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        if (str[i] == del)
        {               // delimiter
            str[i] = 0; // split
            spaces++;
        }
    }

    char **splited = malloc(sizeof(char *) * ++spaces);

    int cnt = 0;
    splited[cnt++] = str;

    for (int i = 0; i < len; i++)
    {
        if (!str[i])
            splited[cnt++] = str + i + 1; // offset by i+1
    }

    splited[cnt++] = 0; // terminate the array

    return (const char **)splited;
}

static const char *findexec(const char *name, const char *path)
{
    if (*name == '/' || *name == '.')
    {
        if(access(name, F_OK) != 0) // if we provide the full path we just check if it exists
            return NULL;
        return name;
    }
    printf("%s\n",path);
    char **pathenv = (char **)split((char *)path, ':');
    void *addr = pathenv;
    while (*pathenv)
    {
        char buffer[256]; // buffer
        sprintf(buffer, "%s/%s", *pathenv, name);
        if(access(buffer, F_OK) == 0)
        {
            char *n = malloc(256); // allocate on heap
            memset(n,0,255); // clear str
            memcpy(n,buffer,strlen(buffer)); // copy
            return n; // return it
        }
        pathenv++;
    }
    free(addr); // free
    return NULL; // fail
}

static const int executea(const char *path, char *argv[], const char *pathenv)
{
    char *fullpath = (char *)path;                // full path
    if (path[0] != '/' || path[0] != '.') // if we don't provide the full path we try to stick the relative path to the path variable
        fullpath = (char *)findexec(fullpath,pathenv);

    if (fullpath == NULL) return -69; // fail

    argv[0] = fullpath; // set to the full path

    int pid;
    switch (pid = vfork()) // spawn child
    {
    case 0: // child
    {
        execv(fullpath, argv); // execute
        break;
    }
    default:
        break; // do nothing
    }

    int status;
    waitpid(pid, &status, 0); // wait for pid to quit
    return status;
}

static const int execute(const char *path, const char *pathenv)
{
    char *argv[] = {(char *)path, NULL};
    return executea(path, argv, pathenv); // wrap the argv
}

static const char readchar()
{
    char c = 0;
    while (!read(STDIN_FILENO, &c, 1))
        ;     // wait for a byte from stdin
    return c; // return character
}

static const int readline(char *buff, int len)
{
    for (int i = 0; i < len; i++)
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
    buff[len - 1] = 0; // terminate string
    return len;        // return max len
}