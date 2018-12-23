#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  pid_t pid;

  if ((pid = fork()) < 0) {
    perror("fork error");
    exit(1);
  } else if (pid == 0) {
    if (execl("/tmp/a.out", (char*)0) < 0) {
      perror("execlp error");
      exit(2);
    }
  }
}
