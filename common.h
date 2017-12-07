//
// Created by nuclearcoder on 2017-12-03.
//

#ifndef SYS_PROJECT_COMMON_H
#define SYS_PROJECT_COMMON_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>

#define _ERR(cond, name, block) \
    if (cond) {\
        perror(name);\
        block;\
    }

#define ERR(cond, name)         _ERR(cond, name, exit(EXIT_FAILURE))
#define ERRH(cond, name, hook)  _ERR(cond, name, hook; exit(EXIT_FAILURE))
#define ERRN(cond, name)        _ERR(cond, name, )
#define ERRNH(cond, name, hook) _ERR(cond, name, hook)


#ifdef DEBUG
#define __PASTER(X)             #X
#define __RESOLVER(X)           __PASTER(X)

#define pDebugV(str, ...)       printf("[DEBUG " __FILE__ ":" __RESOLVER(__LINE__) "] " str "\n", ##__VA_ARGS__)
#define pDebug(str)             printf("[DEBUG " __FILE__ ":" __RESOLVER(__LINE__) "] " str "\n")
#else
#define pDebugV(str, ...)
#define pDebug(str)
#endif


#endif //SYS_PROJECT_COMMON_H
