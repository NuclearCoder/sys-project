//
// Created by nuclearcoder on 08/11/17.
//

#include "headers.h"

#include "clients.h"
#include "misc.h"
#include "commands.h"

int errcl;

#define CLERR_THROW(cond, num) if (cond) { errcl = num; return -1; }

void perrorcl(void) {
    switch (errcl) {
    case CLERR_NONE:
        fprintf(stderr, "No error.\n");
        break;
    case CLERR_TERMINATE:
        fprintf(stderr, "Terminated by client.\n");
        break;
    case CLERR_READ_FAILED:
        perror("FIFO read failed");
        break;
    case CLERR_FIFO_CLOSED:
        fprintf(stderr, "FIFO closed prematurely.\n");
        break;
    case CLERR_WRONG_TERM:
        fprintf(stderr, "Wrong terminating constant.\n");
        break;
    default:
        fprintf(stderr, "Unknown error: %d\n", errcl);
    }
}

int handle_client(int fd) {
    int r;

    /*
     * the command ID, an unsigned integer
     */
    uint32_t cid;

    // read enough bytes from the fifo
    r = exactread(fd, &cid, sizeof(cid));
    CLERR_THROW(r == -1, CLERR_READ_FAILED)
    CLERR_THROW(r == 1, CLERR_FIFO_CLOSED)

    if (handle_command(cid) == -1) {
        return -1;
    }

    uint32_t term;
    r = exactread(fd, &term, sizeof(term));
    CLERR_THROW(r == -1, CLERR_READ_FAILED)
    CLERR_THROW(r == 1, CLERR_FIFO_CLOSED)
    CLERR_THROW(term == 0xF1F0BEEF, CLERR_WRONG_TERM)

    puts("Received terminating constant.");

    // everything went fine, reset error code and return 0
    errcl = CLERR_NONE;
    return 0;
}

int handle_command(uint32_t id) {
    CLERR_THROW(id == CMD_TERMINATE, CLERR_TERMINATE)

    printf("Received command %d.\n", id);

    return 0;
}