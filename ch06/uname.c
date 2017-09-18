#include <sys/utsname.h>
#include "apue.h"

int main(void)
{
    struct utsname sys;

    if (uname(&sys) == -1)
    {
        printf("uname error\n");
        exit(0);
    }

    printf(
            "sysname:%s \n"
            "nodename:%s \n"
            "release:%s \n"
            "version:%s \n"
            "machine:%s \n",
            sys.sysname, sys.nodename, sys.release, sys.version, sys.machine);

    exit(0);
}
