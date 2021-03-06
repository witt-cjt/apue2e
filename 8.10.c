#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/resource.h>

#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>

char *env_init[] = { "USER=unkown", "PATH=/tmp", NULL };

int
main(void)
{
  pid_t pid;

  if ((pid = fork()) < 0) {
    printf("fork error\n");
    exit(1);
  } else if (pid == 0) {
    sleep(5);
    if (execle("/Volumes/DiDi/Projects/github/witt-cjt/apue2e/echoall", "-echoall", "myarg1",
               "MY ARG2", (char *)0, env_init) < 0) {
      perror("execle error");
      exit(2);
    }
  }

  printf("before waitpid\n");
  if (waitpid(pid, NULL, 0) < 0) {
    printf("waitpid error\n");
    exit(3);
  }
  printf("after waitpid\n");

  if (setenv("PATH", "/Volumes/DiDi/Projects/github/witt-cjt/apue2e", 1) < 0) {
    perror("setenv error");
    exit(4);
  }

  if ((pid = fork()) < 0) {
    printf("fork error\n");
    exit(5);
  } else if (pid == 0) {
    if (execlp("a.sh", "a.sh", "only 1 arg", (char *)0) < 0) {
      perror("execlp error");
      exit(6);
    }
  }

  if ((pid = fork()) < 0) {
    printf("fork error\n");
    exit(5);
  } else if (pid == 0) {
    if (execl("/Volumes/DiDi/Projects/github/witt-cjt/apue2e/a.sh", "a.sh", "only 1 arg", (char *)0) < 0) {
      perror("execl error");
      exit(6);
    }
  }
}
