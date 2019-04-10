#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int
main(void)
{
  int fd;
  int size = 100*(1<<20);
  void *ptr;

  fd = open("/tmp/largefile.dat", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  lseek(fd, size - 1, SEEK_SET);
  write(fd, " ", 1);
  ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, fd, 0);
  memset(ptr, 65, size);
  pause();
}
