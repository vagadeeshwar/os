#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sighup();
void sigint();
void sigquit();
void sigstop();
void sigcont();

pid_t pid;

int main()
{
    pid = fork();
    if (pid == 0)
    {
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGSTOP, sigstop);
        signal(SIGCONT, sigcont);
        signal(SIGQUIT, sigquit);
        for (;;)
            ;
    }
    else
    { /* pid holds id of child */
        printf("\nPARENT: sending SIGHUP\n\n");
        kill(pid, SIGHUP);
        sleep(15); /* pause for 3 secs */
        printf("\nPARENT: sending SIGSTOP\n\n");
        kill(pid, SIGSTOP);
        sleep(15);
        printf("\nPARENT: sending SIGCONT\n\n");
        kill(pid, SIGCONT);
        sleep(15); /* pause for 3 secs */
        printf("\nPARENT: sending SIGQUIT\n\n");
        kill(pid, SIGQUIT);
        sleep(15);
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
void sigcont()
{
    signal(SIGCONT, sigcont);
    printf("CHILD: I have received a SIGCONT, I am awake\n");
}
void sigstop()
{
    signal(SIGSTOP, sigstop);
    printf("CHILD: I have received a SIGSTOP, Stopping\n");
}