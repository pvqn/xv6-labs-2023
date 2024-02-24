#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"


void primes(int fd)
{
    int num;
    read(fd,&num,4);
    printf("prime %d \n", num);
    int p[2];
    pipe(p);
    int t=-1;
    while (1)
    {
        //check end of file or not
        int n=read(fd,&t,4);
        if (n<=0) break;
        if (t%num!=0)
        {
            write(p[1],&t,4);
        }
    }
    if (t==-1)
    {
        close(p[1]);
        close(p[0]);
        close(fd);
        return;
    }
    int pid=fork();
    if (pid==0)
    {
        close(p[1]);
        close(fd);
        primes(p[0]);
        close(p[0]);

    }
    else 
    {
        close(fd);
        close(p[0]);
        close(p[1]);
        wait(0);

    }
    
}

int main()
{
    int p[2];
    pipe(p);
    for (int i=2; i<=35; ++i)
    {
        int n=i;
        write(p[1],&n,4);
    }
    close(p[1]);
    primes(p[0]);
    close(p[0]);

    exit(1);
}