//#include "apue.h"
#include "synchronous.c"
//#include <stdio.h>
//#include <sys/types.h>

int main(void)
{
    pid_t pid;

    TELL_WAIT();

    if (pid = fork() < 0)
        perror("fork errro");
    else if (pid == 0) {
        WAIT_PARENT();
        printf("output from child\n");
    } else {
        printf("output from parent\n");
        TELL_CHILD(pid);
    }

    exit(0);
}

