//
// Created by nuclearcoder on 08/11/17.
//

#include "../common.h"

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

bool strsnequ(const char *str1, const char *str2, size_t n) {
    if (str1 == NULL || str2 == NULL) {
	    return false;
    }

    size_t i = 0;

    while (i < n && *str1 != '\0' && *str1 != ' ') {
	    if (*str1++ != *str2++)
	        return false;
        i++;
    }
    if (*str2 == '\0' || *str2 == ' ')
	    return true;
    return false;
}
