#include "headers.h"

#include "pipes.h"

void create_pipe(const char *pathname) {
    ERR(mkfifo(pathname, 0666) == -1, "create_pipe")
}

int open_pipe(const char *pathname) {
    int fd = open(pathname, O_RDONLY);
    ERR(fd == -1, "open_pipe")
    return fd;
}

void close_pipe(int pipefd) {
    ERR(close(pipefd) == -1, "close_pipe")
}
