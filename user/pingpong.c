#include "kernel/types.h"
#include "user.h"
#include "kernel/fcntl.h"
void main()
{
    int p[2];
    char buf[100];
    pipe(p);
    int pid=fork();
    if (pid==0)
    {
        write(p[1],"ping",4);
        printf("%d: received ping \n", getpid());
    }
    else 
    {
        wait(0);
        read(p[0], buf,4);
        printf("%d: received pong \n", getpid());
    }

}