#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

int daemon_init(void)
{
   char c;
   pid_t pid;
   if(( pid = fork()) < 0) return (-1);
   else if(pid != 0) exit(0);
   setsid();
   printf("pid=%ld, pgrp=%ld, sid=%ld\n", (long)getpid(), (long)getpgrp(), (long)getpgrp());
   return (0);
}

int main(void)
{
   daemon_init();
   if(execlp("ps", "ps", "ajx", (char*)0) < 0) {
      printf("execlp error");
      exit(1);
   }
   exit(0);
}
