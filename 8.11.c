#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(void)
{
  int euid;

  printf("uid: %d\n", getuid());
  printf("euid: %d\n", geteuid());

  euid = geteuid();

  if (setuid(getuid()) < 0) {
    perror("setuid failed");
    exit(1);
  }
  printf("uid: %d\n", getuid());
  printf("euid: %d\n", geteuid());

  if (setuid(euid) < 0) {
    perror("setuid failed");
    exit(2);
  }
  printf("uid: %d\n", getuid());
  printf("euid: %d\n", geteuid());
}
