#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int
main(void)
{
    long num;

    num = sysconf(_SC_OPEN_MAX);
    printf("OPEN_MAX: %d\n", num);

    num = sysconf(_SC_NPROCESSORS_ONLN);
    printf("NPROCESSORS_ONLN: %d\n", num);

    num = sysconf(_SC_NPROCESSORS_CONF);
    printf("NPROCESSORS_CONF: %d\n", num);

    // 3.7 ssize_t read(int fd, void *buf, size_t numbytes)
    printf("SSIZE_MAX: %d\n", sysconf(_SC_SSIZE_MAX));

    num = sysconf(_SC_NGROUPS_MAX);
    printf("NGROUPS_MAX: %d\n", num);

    printf("CHILD_MAX: %d\n", sysconf(_SC_CHILD_MAX));
}
