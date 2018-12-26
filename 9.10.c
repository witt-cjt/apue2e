#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

static void
sig_hup(int signo)
{
  printf("SIGHUP received %d, pid = %d\n", signo, getpid());
  fflush(stdout);
}

static void
sig_cont(int signo)
{
  printf("SIGCONT received %d, pid = %d\n", signo, getpid());
  fflush(stdout);
}

static void
pr_ids(char *name)
{
  printf("%s : pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n",
         name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO));
  fflush(stdout);
}

int
main(void)
{
  char c;
  pid_t pid;

  pr_ids("parent");
  if ((pid = fork()) < 0) {
    perror("fork error");
    exit(1);
  } else if (pid > 0) {
    sleep(3);
    exit(0);
  } else {
    pr_ids("child");
    signal(SIGHUP, sig_hup);
    signal(SIGCONT, sig_cont);
    kill(getpid(), SIGTSTP);
    pr_ids("child");
    if (read(STDIN_FILENO, &c, 1) != 1) {
      printf("read error from controlling TTY, errno = %d\n",
             errno);
    }
    _exit(0);
  }
}
