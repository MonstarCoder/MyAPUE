//#include "apue.h"
#include "synchronous.c"
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;

    TELL_WAIT();

    if ((pid = fork()) < 0)
        perror("fork errro");
    else if (pid == 0) {
        WAIT_PARENT();
        char buf1[] = "output from child\n";
        write(STDOUT_FILENO, buf1, sizeof(buf1) - 1);
    } else {
        char buf2[] = "output from parent\n";
        write(STDOUT_FILENO, buf2, sizeof(buf2) - 1);
        TELL_CHILD(pid);
    }

    exit(0);
}

