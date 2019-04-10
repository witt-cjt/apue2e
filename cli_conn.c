#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#define CLI_PATH "/var/tmp/"
#define CLI_PERM S_IRWXU

int
main(void)
{
    int fd, size;
    struct sockaddr_un un;

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("socket failed\n");
        exit(1);
    }

    un.sun_family = AF_UNIX;
    sprintf(un.sun_path, "%s%05d", CLI_PATH, getpid());
    size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
    unlink(un.sun_path);
    if (bind(fd, (struct sockaddr *) &un, size) < 0) {
        printf("bind failed\n");
        exit(1);
    }
    if (chmod(un.sun_path, CLI_PERM) < 0) {
        printf("chmod failed\n");
        goto error;
    }
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, "foo.socket");
    size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
    if (connect(fd, (struct sockaddr *) &un, size) < 0) {
        perror("connect failed");
        goto error;
    }
    if (write(fd, "conect success", sizeof("conect success")) < 0) {
        perror("write error");
        goto error;
    }
    exit(0);

error:
    sprintf(un.sun_path, "%s%05d", CLI_PATH, getpid());
    unlink(un.sun_path);
    exit(1);
}
