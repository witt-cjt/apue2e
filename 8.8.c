#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/resource.h>

#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>

int
main(void)
{
  pid_t pid;
  int stat_loc;
  struct rusage rusage;

  if ((pid = fork()) < 0)
    err(0, "fork error");
  else if (pid == 0) {
    // first child process
    if ((pid = fork()) < 0)
      err(0, "fork error");
    if (pid > 0)
      exit(0);

    // second child process
    sleep(100);
    exit(0);
  }

  // parent process
  printf("child: %d\n", pid);
  sleep(5);
  if ((pid = wait3(&stat_loc, WNOWAIT, &rusage)) < 0) {
    perror("wait error");
    exit(1);
  }
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

  printf("ru_stime: %ld.%d\n", rusage.ru_stime.tv_sec, rusage.ru_stime.tv_usec);
  printf("ru_utime: %ld.%d\n", rusage.ru_utime.tv_sec, rusage.ru_utime.tv_usec);
  printf("ru_maxrss: %ld\n", rusage.ru_maxrss);
  printf("ru_ixrss: %ld\n", rusage.ru_ixrss);
  printf("ru_idrss: %ld\n", rusage.ru_idrss);
  printf("ru_isrss: %ld\n", rusage.ru_isrss);
  printf("ru_nswap: %ld\n", rusage.ru_nswap);
  printf("ru_nvcsw: %ld\n", rusage.ru_nvcsw);
  printf("ru_nivcsw: %ld\n", rusage.ru_nivcsw);
  printf("ru_minflt: %ld\n", rusage.ru_minflt);
  printf("ru_majflt: %ld\n", rusage.ru_majflt);
  printf("ru_msgsnd: %ld\n", rusage.ru_msgsnd);
  printf("ru_msgrcv: %ld\n", rusage.ru_msgrcv);
  printf("ru_inblock: %ld\n", rusage.ru_inblock);
  printf("ru_oublock: %ld\n", rusage.ru_oublock);
  printf("ru_nsignals: %ld\n", rusage.ru_nsignals);
}
