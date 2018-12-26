#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
  hang in macos
*/

static void
my_alarm(int signo)
{
  struct passwd *rootptr;

  signal(SIGALRM, my_alarm);
  printf("in signal handler, signo: %d\n", signo);
  if ((rootptr = getpwnam("root")) == NULL) {
    perror("getpwnam(root) error");
  }
  alarm(1);
}

int
main(void)
{
  struct passwd *ptr;

  signal(SIGALRM, my_alarm);
  signal(SIGSEGV, SIG_IGN);
  alarm(1);
  for ( ; ; ) {
    if ((ptr = getpwnam("chujitao")) == NULL) {
      perror("getpwnam error");
      exit(1);
    }
    if (strcmp(ptr->pw_name, "chujitao") != 0)
      printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
  }
}
