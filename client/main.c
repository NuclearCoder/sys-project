//
// Created by nuclearcoder on 30/11/17
// 

#include "headers.h"

#include "shm.h"
#include "sem.h"
#include "fifo.h"

int main(int argc, char **argv) {
    // read pathname and command from argument
    const char *pathname;
    const char *command;

    pathname = (argc > 1) ? argv[1] : "cmdqueue";

    if (argc > 2) {
        command = argv[2];
    } else {
        command = NAME(TERMINATE);
    }

    // pid will identify this process uniquely during its lifetime
    pid_t pid = getpid();

    // create shared memory segment and map it
    pmmap_t *map = create_and_map_shm(pid);
    
    init_sem(map);

    int fd = open_fifo(pathname);

    pset(&map->p, pid, command);

    write(fd, &map->p, sizeof(struct packet));
    close(fd);

    wait_sem(map);

    printf("Response: %s\n", map->p.data);

    return 0;
}
