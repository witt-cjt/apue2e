#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

void
my_thread(void)
{
  printf("pid: %d\n", syscall(gettid));
  printf("tid: %d\n", pthread_self());
}

int
main(void)
{
  pthread_t tidp;
  int err;

  err = pthread_creat(&tidp, NULL, my_thread, NULL);
  if (err != 0) {
    printf("can't create thread: %s\n", strerror(err));
    exit(1);
  }
  sleep(1);
  exit(0);
}
