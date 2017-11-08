//
// Created by nuclearcoder on 08/11/17.
//

#include "headers.h"

#include "misc.h"

int exactread(int fd, void *buf, size_t len) {
    ssize_t br;
    int count;

    count = 0;
    do {
        br = read(fd, buf + count, len - count);
        if (br == -1) return -1;
        else if (br == 0) return 1;

        count += br;
    } while (count != len);

    return 0;
}