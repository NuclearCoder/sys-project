//
// Created by nuclearcoder on 08/11/17.
//

#include "headers.h"

#include "misc.h"

int exact_read(int fd, void *buf, size_t len) {
    ssize_t br;
    size_t count;

    count = 0;
    while (count != len) {
        br = read(fd, (char *) buf + count, len - count);
        if (br == -1) return -1;
        else if (br == 0) return 1;

        count += (size_t) br;
    };

    return 0;
}