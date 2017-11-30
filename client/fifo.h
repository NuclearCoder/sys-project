//
// Created by nuclearcoder on 30/11/17
//

#ifndef SYS_PROJECT_FIFO_H
#define SYS_PROJECT_FIFO_H

int open_fifo(const char *pathname);

int pset(struct packet *p, int id, const char *format, ...);

#endif // SYS_PROJECT_FIFO_H
