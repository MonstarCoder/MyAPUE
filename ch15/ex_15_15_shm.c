#include <sys/stat.h>
#include <sys/shm.h>
#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>
#include "synchronous.c"

#define	NLOOPS		1000
#define	SIZE		sizeof(long)	/* size of shared memory area */

static int
update(long *ptr)
{
	return((*ptr)++);	/* return value before increment */
}

int
main(void)
{
	int		fd, i, counter, shmid;
	pid_t	pid;
	void	*area;


	if ((fd = open("/dev/zero", O_RDWR)) < 0)
		err_sys("open error");
	if ((shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666)) == -1)
		err_sys("Shared Memory Created error");
	area = shmat(shmid, NULL, 0);

	close(fd);		/* can close /dev/zero now that it's mapped */

	TELL_WAIT();

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {			/* parent */
		for (i = 0; i < NLOOPS; i += 2) {
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);

			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	} else {						/* child */
		for (i = 1; i < NLOOPS + 1; i += 2) {
			WAIT_PARENT();

			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);

			TELL_PARENT(getppid());
		}
	}

	exit(0);
}
