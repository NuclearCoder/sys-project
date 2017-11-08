//
// Created by nuclearcoder on 07/11/17.
//

#ifndef SYS_PROJECT_PIPES_H
#define SYS_PROJECT_PIPES_H

void create_pipe(const char *pathname);

void unlink_pipe(const char *pathname);

int open_pipe(const char *pathname);

void close_pipe(int pipefd);

#endif //SYS_PROJECT_PIPES_H
