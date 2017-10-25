#include "apue.h"
#include "init.c"

int
main(void)
{
	FILE *fp;
	char *p;

	daemonize("getlog");
	p = getlogin();
	fp = fopen("./getlog.out", "w");
	if (fp != NULL) {
		if (p == NULL)
			fprintf(fp, "no login name\n");
		else
			fprintf(fp, "login name: %s\n", p);
	}
    printf("error!\n");
	exit(0);
}
