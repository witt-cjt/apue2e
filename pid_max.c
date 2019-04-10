#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *
my_fnc(void *arg)
{
  arg = NULL;
  pause();
  return NULL;
}

int
main(void)
{
  int i;
  pthread_t thread[2000];

  for (i = 0; i < 2000; i++) {
    if (pthread_create(&thread[i], NULL, my_fnc, NULL) != 0) {
      printf("n: %d\n", i);
      perror("pthread_create failed");
      exit(1);
    }
  }
}
