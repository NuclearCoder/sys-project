//
// Created by nuclearcoder on 30/11/17
//

#include "../common.h"

#include "clients.h"

int errcl;

void perrorcl(void) {
    switch (errcl) {
    case CLERR_NONE:
        printf("No error.\n");
        break;
    case CLERR_TERMINATE:
        printf("Terminated by client.\n");
        break;
    case CLERR_READ_FAILED:
        printf("E] FIFO read failed: %s\n", strerror(errno));
        break;
    case CLERR_FIFO_CLOSED:
        printf("E] FIFO closed prematurely.\n");
        break;
    case CLERR_SHM_OPEN:
        printf("E] SHM open failed: %s\n", strerror(errno));
        break;
    case CLERR_SHM_UNLINK:
        printf("E] SHM unlink failed: %s\n", strerror(errno));
        break;
    case CLERR_SHM_MMAP:
        printf("E] SHM memory map failed: %s\n", strerror(errno));
        break;
    case CLERR_SEM_POST:
        printf("E] Semaphore post failed: %s\n", strerror(errno));
        break;
    case CLERR_THREAD_ARG:
        printf("E] Could not allocate thread arg: %s\n", strerror(errno));
        break;
    case CLERR_PARSE_RANGE:
        printf("E] Could not parse string: %s\n", strerror(errno));
        break;
    case CLERR_PARSE_NOTHING:
        printf("E] Could not find anything to parse.\n");
        break;
    case CLERR_USER_FAILED:
        printf("E] No such user found.\n");
        break;
    case CLERR_NO_INFO:
        printf("E] Could not fetch information.\n");
        break;
    case CLERR_OUT_OF_HEAP:
        printf("E] Could not allocate on the heap.\n");
    default:
        printf("E] Unknown error: %d\n", errcl);
    }
}
