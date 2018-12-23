#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ./a.out
  parent pid: 84187
  pid: 84188
  pid: 84187
  pid: 84189
*/

static void f1(void), f2(void);

int
main(void)
{
  printf("parent pid: %d\n", getpid());
  f1();
  exit(0);
  f2();
}


static void
f1(void)
{
  pid_t pid;

  if ((pid = vfork()) < 0) {
    printf("vfork error\n");
    exit(1);
  }
  printf("%d\n", pid);
}


static void
f2(void)
{
  char buf[1000];
  unsigned long i;

  for (i = 0; i < sizeof(buf); i++) {
    buf[i] = 0;
  }
}
