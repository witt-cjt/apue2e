#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>

int
main(void)
{
  pid_t pid;
  int stat_loc;

  if ((pid = fork()) < 0)
    err(0, "fork error");
  else if (pid == 0) {
      exit(0);
  } else {
    printf("child: %d\n", pid);
    sleep(10);
    if ((pid = wait(&stat_loc)) < 0)
      perror("wait error");
    printf("child %d terminated\n", pid);

    if (WIFEXITED(stat_loc))
      printf("child terminated normally: %d\n", WEXITSTATUS(stat_loc));
    if (WIFSIGNALED(stat_loc)) {
      printf("child terminated by a signal: %d\n", WTERMSIG(stat_loc));

      if (WCOREDUMP(stat_loc))
        printf("child terminated with coredump\n");
    }
    if (WIFSTOPPED(stat_loc))
      printf("child has stopped and can be restarted: %d\n", WSTOPSIG(stat_loc));
  }
}
