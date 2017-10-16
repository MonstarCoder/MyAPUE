#include <dirent.h> /*opendir()*/
#include <unistd.h> /*execl(),fcntl()*/
#include <fcntl.h>
#include <sys/types.h>
#include "apue.h"

int main(void)
{
    DIR *dir;
    pid_t pid;
    int val, fd;
    char buf[10]; /*for save fd*/

    dir = opendir("/");
    fd = dirfd(dir);

    if((val = fcntl(fd,F_GETFD,0)) < 0)
        perror("fcntl");
    if(val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("clsose-on-exec is off\n");

    sprintf(buf,"%d\0",fd);

    if((pid = fork()) < 0)
        perror("fork");
    else if(pid == 0)
    {
        execl("./exec_opendir_child", "exec_opendir_child", buf, NULL);
        exit(0);
    }
    sleep(2);

    return 0;
}
