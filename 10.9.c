#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void sig_SIGUSR1(signo) {
  printf("received signal %d\n", signo);
}

int
main(void)
{
  sigset_t sigset;

  signal(SIGUSR1, sig_SIGUSR1);
  sigaddset(&sigset, SIGUSR1);
  // sigprocmask(SIG_BLOCK, &sigset, NULL);
  printf("block signal\n");
  if (kill(getpid(), SIGUSR1) < 0) {
    perror("kill error");
    exit(1);
  }
  printf("signal sent\n");
  printf("unblock signal\n");
  // sigprocmask(SIG_UNBLOCK, &sigset, NULL);
  printf("exit\n");
  exit(0);
}

