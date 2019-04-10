#include <signal.h>
#include <stdio.h>

int
main(void)
{
  int i = 0;
  for ( ; i < NSIG ; i++) {
    printf("signo: %d, sig_name: %s\n", i, sys_siglist[i]);
  }
}

int sig2str(int signo, char *str);

int
sig2str(int signo, char *str)
{
  if (str == NULL) {
    return -1;
  }
  if (signo < 1 || signo > NSIG) {
    str = "unknow signal";
    return -1;
  }

  str = (char *)sys_siglist[signo];
  return 0;
}
