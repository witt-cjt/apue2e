#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sig_alarm(signo) {
  printf("received signal: %d\n", signo);
}

int
main(void)
{
  unsigned int nsecs;
  sig_t sig;

  if ((nsecs = alarm(2)) > 0) {
    printf("alarm already exists\n");
    alarm(nsecs);
  }
  if ((sig = signal(SIGALRM, sig_alarm)) == SIG_ERR) {
    perror("set signal handler error");
    exit(1);
  }
  if (pause() == -1) {
    perror("pause returnd");
  }
  if (signal(SIGALRM, sig) == SIG_ERR) {
    perror("set signal handler error");
    exit(2);
  }
  printf("finished\n");
  exit(0);
}
