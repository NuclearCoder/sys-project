//
// Created by nuclearcoder on 2017-12-03.
//

#ifndef SYS_PROJECT_CLIENT_H
#define SYS_PROJECT_CLIENT_H

typedef int (*ccallback_t)(pmmap_t *);

#define callback(name) int name (pmmap_t *map)

void set_callback(ccallback_t cb);

void run_client(const char *fifoname, const char *command, ...);

#endif //SYS_PROJECT_CLIENT_H
