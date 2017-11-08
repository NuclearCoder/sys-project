//
// Created by nuclearcoder on 07/11/17.
//

#ifndef SYS_PROJECT_HEADERS_H
#define SYS_PROJECT_HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define _ERR(cond, name, block) \
    if (cond) {\
        perror(name);\
        block;\
    }

#define ERR(cond, name)         _ERR(cond, name, exit(EXIT_FAILURE))
#define ERRH(cond, name, hook)  _ERR(cond, name, hook; exit(EXIT_FAILURE))
#define ERRN(cond, name)        _ERR(cond, name, )
#define ERRNH(cond, name, hook) _ERR(cond, name, hook)

#endif //SYS_PROJECT_HEADERS_H
