#include <unistd.h>
#include <stdlib.h>

int
main(void)
{
  if (fork() > 0)
    sleep(50);
  exit(0);
}
