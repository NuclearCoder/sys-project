//
// Created by nuclearcoder on 08/11/17.
//

#include "headers.h"

#include "clients.h"
#include "misc.h"
#include "commands.h"

static int errcl;

#define CLERR_THROW(cond, num) if (cond) { errcl = num; return num; }

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
    case CLERR_WRONG_TERM:
        printf("E] Wrong terminating constant.\n");
        break;
    default:
        printf("E] Unknown error: %d\n", errcl);
    }
}

int handle_client(int fd) {
    int r;

    struct packet p;

    r = exact_read(fd, &p, sizeof(p));
    CLERR_THROW(r == -1, CLERR_READ_FAILED)
    CLERR_THROW(r == 1, CLERR_FIFO_CLOSED)

    printf("Client: %d\n", p.id);



    int ret = handle_command(p);

    // everything went fine, reset error code and return 0
    return ret;
}

int handle_command(struct packet p) {
    printf("Received command '%s'.\n", p.data);

    CLERR_THROW(strcmp("term", p.data) == 0, CLERR_TERMINATE)

    return 0;
}