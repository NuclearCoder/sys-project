//
// Created by nuclearcoder on 07/11/17.
//

#include "headers.h"

#include "pipes.h"

void create_pipe(const char *pathname) {
    ERR(mkfifo(pathname, 0666) == -1, "create_pipe")
}

void unlink_pipe(const char *pathname) {
    ERR(unlink(pathname) == -1, "unlink_pipe")
}

int open_pipe(const char *pathname) {
    // open in read/write so the pipe stays alive
    int fd = open(pathname, O_RDWR);
    ERR(fd == -1, "open_pipe")
    return fd;
}

void close_pipe(int pipefd) {
    ERR(close(pipefd) == -1, "close_pipe")
}
