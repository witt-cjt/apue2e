#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/resource.h>

#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  int i;
  char **ptr;
  extern char **environ;

  for (i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);

  for (ptr = environ; *ptr != 0; ptr++)
    printf("%s\n", *ptr);
}
