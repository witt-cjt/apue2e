#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>

int
main(void)
{
    int fd, size;
    struct sockaddr_un un;

    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, "foo.socket");
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("socket failed\n");
        exit(1);
    }
    unlink("foo.socket");
    size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
    if (bind(fd, (struct sockaddr *) &un, size) < 0) {
        perror("bind failed");
        exit(1);
    }
    if (listen(fd, 100) < 0) {
        perror("listen failed");
        exit(1);
    }

    int clifd, len;
    len = sizeof(un);
    if ((clifd = accept(fd, (struct sockaddr *) &un, (socklen_t *)&len)) < 0) {
        perror("accept failed");
        exit(1);
    }
    printf("%s\n", un.sun_path);
    unlink(un.sun_path);
    char buf[1024];
    while (read(clifd, buf, 1024) > 0) {
        puts(buf);
    }
    exit(0);
}
