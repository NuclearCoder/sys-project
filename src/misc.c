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
        if (br == -1) {
            // if it's an interrupt, just restart the call
            if (errno == EINTR) {
                count = 0;
                continue;
            } else {
                return -1;
            }
        }
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

int parseint(const char *str, int *nptr) {
    char *endptr;
    long val;

    errno = 0;
    val = strtol(str, &endptr, 0);

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        return -1;
    } else if (endptr == str || *endptr != '\0') {
        // parse only a full integer (greedy parse)
        return 1;
    }

    *nptr = (int) val;

    return 0;
}
