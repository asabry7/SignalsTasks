#define _GNU_SOURCE
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        char msg[] = "Usage: command <pid> <value>\n";
        if (write(STDOUT_FILENO, msg, strlen(msg)) == -1)
        {
            perror("Error in write:");
        }

        exit(EXIT_FAILURE);
    }

    int PID = atoi(argv[1]);
    int value = atoi(argv[2]);

    union sigval mysigval;
    mysigval.sival_int = value;

    if (sigqueue(PID, SIGRTMIN + 5, mysigval) == -1)
    {
        perror("Error in sigqueue:");
        exit(EXIT_FAILURE);
    }

    return 0;
}