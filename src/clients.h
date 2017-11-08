//
// Created by nuclearcoder on 07/11/17.
//

#ifndef SYS_PROJECT_CLIENTS_H
#define SYS_PROJECT_CLIENTS_H

/* Prints client error if there was one. */
void perrorcl(void);

/* Client error code. */
extern int errcl;

enum {
    CLERR_NONE = 0,
    CLERR_TERMINATE,
    CLERR_READ_FAILED,
    CLERR_FIFO_CLOSED,
    CLERR_WRONG_TERM
};

/* Returns -1 on error and errcl is set appropriately. */
int handle_client(int fd);

/* Returns -1 on error and errcl is set appropriately. */
int handle_command(uint32_t id);

#endif //SYS_PROJECT_CLIENTS_H
