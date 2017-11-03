#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include "synchronous.c"

#define BUF_SIZE 100
static volatile sig_atomic_t sigflag;
//static long last_off=0;
/*
void int2chars(char* chars, int count, char* cat)
{
	int b=0, flag = count;
	
	do{
		flag /= 10;
		b++;
	}while(flag);
	
	chars[b--] = '\0';
	while(b>=0){
		chars[b--] = count%10 + '0';
		count /= 10;
	}
	
	strcat(chars, cat);
	
	return ;
}

int chars2int(char* chars)
{
	int count = 0, flag = 1;
	
	int i = strlen(chars) - 1;
	
	while(i >= 0)
	{
		count += (chars[i] - '0') * flag;
		
		flag *= 10;
		
		i--;
	}
	
	return count;
}
*/
int main(int argc, char *argv[])
{
	FILE *fp;
	pid_t pid;
	int count = 0, shmid;
	char buf[1024] = "";
	long *lastoffptr;
	
	shmid=shmget(IPC_PRIVATE, BUF_SIZE, IPC_CREAT|0666);
	
	if(shmid == -1)
	{
		printf("Shared Memory Created error...\n");
		exit(-127);
	}

	lastoffptr = shmat(shmid, NULL, 0);
	
	if((fp = fopen("tt.txt", "w+")) < 0)	
	{
		perror("open error or write error!");
		exit(-1);
	}
	
	
	fprintf(fp, "0\ttest\n");
	fflush(fp);
	TELL_WAIT();

	alarm(2);
	
	if((pid = fork()) > 0)//parent
	{
		while(1){
			WAIT_CHILD();
						
			printf("the current ftell=%ld\n", ftell(fp));
			
			fseek(fp, *lastoffptr, SEEK_SET);
			fscanf(fp, "%d\t%s\n", &count, buf);
			printf("parent read from the file count=%d.\n", count);
			
			*lastoffptr = ftell(fp);
			fprintf(fp,"%d\t%s\n", count+1, "parent");
			fflush(fp);
			
			TELL_CHILD(pid);
		}
	}else //child
	{
		while(1){
			
			fseek(fp, *lastoffptr, SEEK_SET);
			fscanf(fp, "%d\t%s\n", &count, buf);
			printf("child read from the file count=%d.\n", count);
			
			*lastoffptr = ftell(fp);
			if(fprintf(fp,"%d\t%s\n", count+1, "child")<0){printf("child write error\n");}
			fflush(fp);
			
			
			TELL_PARENT(getppid());
			WAIT_PARENT();
		}
	}
	
	fclose(fp);
	return 0;
}

