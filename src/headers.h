#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR(cond, name) \
    if (cond) {\
        perror(name);\
        exit(EXIT_FAILURE);\
    }

#define ERRH(cond, name, hook) \
    if (cond) {\
        perror(name);\
        hook\
        exit(EXIT_FAILURE);\
    }

#endif // __HEADER_H__
