#include "apue.h"
#include "../APUE/apue.3e/lib/pathalloc.c"

int main()
{
    char *ptr;
    size_t size;
    if (chdir("/home/monstar/MyAPUE/ch04") < 0)
        err_sys("chdir failed");
    ptr = path_alloc(&size);
    if (getcwd(ptr, size) == NULL)
        err_sys("getcwd failed");
    printf("cwd = %s\n", ptr);
    exit(0);
}
