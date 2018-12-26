#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        if (setsid() < 0){
            perror("setsid error");
            exit(2);
        }

        printf("pid: %d, ppid: %d, pgrp: %d, sid: %d\n",
            getpid(), getppid(), getpgrp(), getsid(0));

        if (open("/dev/tty", O_RDONLY) == -1){
            perror("open /dev/tty error");
            exit(2);
        }

    }

    exit(0);
}
