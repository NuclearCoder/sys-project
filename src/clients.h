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
    CLERR_SHM_OPEN,
    CLERR_SHM_UNLINK,
    CLERR_SHM_MMAP,
    CLERR_SEM_POST,
    CLERR_THREAD_ARG,
    CLERR_PARSE_RANGE,
    CLERR_PARSE_NOTHING,
    CLERR_USER_FAILED,
    CLERR_OUT_OF_HEAP,
    CLERR_NO_INFO
};

#define PACKET_SIZE 32

struct packet {
    int id;
    char data[PACKET_SIZE];
};

typedef struct {
    sem_t sem;
    struct packet p;
} pmmap_t;

/* Returns 0 on success and returns an error code. */
int handle_client(int fd);

/* Callback function for thread */
void *client_thread(void *arg);

/* Returns -1 on error and errcl is set appropriately. */
int handle_command(struct packet *response);

/* Sets id and data for a packet; returns the offset in data to write next */
int pset(struct packet *p, int id, const char *format, ...);

#endif //SYS_PROJECT_CLIENTS_H
