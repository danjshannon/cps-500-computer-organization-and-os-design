#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid != 0)
    { // parent code
        waitpid(pid, &status, 0);
        printf("******* I am the parent!!!\n");
    }
    else
    {
        static char *argv[] = {"ls", "-a", NULL};
        execvp("ls", argv);
    } // main
}