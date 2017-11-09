//
// Created by nuclearcoder on 07/11/17.
//

#ifndef SYS_PROJECT_CLIENTS_H
#define SYS_PROJECT_CLIENTS_H

/* Prints client error if there was one. */
void perrorcl(void);

enum {
    CLERR_NONE = 0,
    CLERR_TERMINATE,
    CLERR_READ_FAILED,
    CLERR_FIFO_CLOSED,
    CLERR_WRONG_TERM
};

#define PACKET_SIZE 1024

struct packet {
    int id;
    char data[PACKET_SIZE];
};

/* Returns 0 on success and returns an error code. */
int handle_client(int fd);

/* Returns -1 on error and errcl is set appropriately. */
int handle_command(struct packet p);

#endif //SYS_PROJECT_CLIENTS_H
