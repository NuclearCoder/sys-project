//
// Created by nuclearcoder on 2017-11-30.
//

#ifndef SYS_PROJECT_HEADERS_H
#define SYS_PROJECT_HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>

#include <string.h>

#include <sys/mman.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
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


#include "../src/clients.h"
#include "../src/commands.h"

#endif // SYS_PROJECT_HEADERS_H
