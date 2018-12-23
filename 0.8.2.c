#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
  vfork exit stdout STDOUT_FILENO
*/

int glob = 6;

int
main(void)
{
  int var;
  pid_t pid;

  var = 88;
  printf("before vfork\n");
  if ((pid = vfork()) < 0) {
    printf("vfork error\n");
    exit(1);
  } else if (pid == 0) {
    glob++;
    var++;
    fclose(stdout);
    exit(2);
  }
  sleep(2);
  printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
  char buf[] = "hello\n";
  if (write(STDOUT_FILENO, buf, 7) != 7) {
    perror("write error");
    exit(1);
  }
  exit(0);
}
