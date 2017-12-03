//
// Created by nuclearcoder on 30/11/17
//

#include "headers.h"

int open_fifo(const char *pathname) {
    int fd = open(pathname, O_WRONLY);
    ERR(fd == -1, "open_fifo")
    return fd;
}

int pset(struct packet *p, int id, const char *format, ...) {
    p->id = id;

    va_list argptr;
    va_start(argptr, format);
    int n = vsnprintf(p->data, PACKET_SIZE, format, argptr);
    va_end(argptr);
    
    return n;
}
