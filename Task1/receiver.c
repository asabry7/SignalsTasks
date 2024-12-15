#define _GNU_SOURCE
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void myHandler(int sig, siginfo_t *info, void *ucontext)
{
    if (sig == (SIGRTMIN + 5))
    {
        char msg[] = "Caught the realtime signal\n";
        if (write(STDOUT_FILENO, msg, strlen(msg)) == -1)
        {
            perror("Error in write:");
            exit(EXIT_FAILURE);
        }

        if (info->si_value.sival_int == 0)
        {
            /* Terminate */
            raise(SIGTERM);
        }

        else if (info->si_value.sival_int == 1)
        {
            /* Abort */
            raise(SIGABRT);
        }
    }
}
int main()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler;

    if (sigaction(SIGRTMIN + 5, &sa, NULL) == -1)
    {
        perror("Error in sigaction:");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for the realtime signal. Receiver PID = %d\n", getpid());

    pause();

    return 0;
}