#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

pid_t pid;

void sighup(); /* routines child will call upon sigtrap */
void sigint();
void sigquit();

int main()
{
    pid = fork();
    if (pid == 0)
    {
        signal(SIGHUP, sighup); /* set function calls*/
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        for (;;)
            ;
    }
    else
    { /* pid holds id of child */
        printf("\nPARENT: sending SIGHUP\n\n");
        kill(pid, SIGHUP);
        sleep(10); /* pause for 3 secs */
        printf("\nPARENT: sending SIGINT\n\n");
        kill(pid, SIGINT);
        sleep(10); /* pause for 3 secs */
        printf("\nPARENT: sending SIGQUIT\n\n");
        kill(pid, SIGQUIT);
        sleep(10);
    }
    return 0;
}
void sighup()
{
    signal(SIGHUP, sighup); /* reset signal */
    printf("CHILD: I have received a SIGHUP\n");
}
void sigint()
{
    signal(SIGINT, sigint); /* reset signal */
    printf("CHILD: I have received a SIGINT\n");
}
void sigquit()
{
    printf("My DADDY has Killed me!!!\n");
    exit(0);
}
