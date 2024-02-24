#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/param.h"

int getcmd(char *buf, int nbuf)
{
    memset(buf, 0, nbuf);
    gets(buf, nbuf);
    if (buf[0] == 0) // EOF*
    {

        return -1;
    }

    return 0;
}

char whitespace[] = " \t\r\n\v";

int gettoken(char **ps, char *es, char **q, char **eq)
{
    char *s;
    int ret;

    s = *ps;
    while (s < es && strchr(whitespace, *s))
        s++;
    if (q)
        *q = s;
    ret = *s;
    switch (*s)
    {
    case 0:
        break;
    default:
        ret = 'a';
        while (s < es && !strchr(whitespace, *s))
            s++;
        break;
    }
    if (eq)
        *eq = s;

    while (s < es && strchr(whitespace, *s))
        s++;
    *ps = s;
    return ret;
}

int main(int argc, char *argv[])
{
    char *xargs[MAXARG];
    for (int i = 1; i < argc; i++)
    {
        // Skip `xargs` cmd name.*
        xargs[i - 1] = argv[i];
    }

    static char buf[MAXARG][100];
    char *q, *eq;
    int j = argc - 1;
    int i = 0;
    // Split each line into array of args.*
    while (getcmd(buf[i], sizeof(buf[i])) >= 0)
    {
        char *s = buf[i];
        char *es = s + strlen(s);
        while (gettoken(&s, es, &q, &eq) != 0)
        {
            // Set end to 0.*
            xargs[j] = q;
            *eq = 0;
            j++;
            i++;
        }
    }

    int pid = fork();
    if (pid == 0)
    {
        exec(xargs[0], xargs);
    }
    wait(0);

    exit(1);
}