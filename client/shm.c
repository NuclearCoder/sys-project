//
// Created by nuclearcoder on 30/11/17
//

#include "../common.h"

#include "../src/clients.h"

#define SHM_NAME_MAX 32

pmmap_t *create_and_map_shm(pid_t id) {
    // create the name
    char name[SHM_NAME_MAX];
    snprintf(name, SHM_NAME_MAX, "/sysp_shm_%d", id);

    // open the shared memory
    int shmid = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0666);
    ERR(shmid == -1, "shm_open")

    // truncate to the right size
    ERR(ftruncate(shmid, sizeof(pmmap_t)) == -1, "ftruncate")

    // map the block
    pmmap_t *map = mmap(NULL, sizeof(pmmap_t),
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED, shmid, 0);
    ERR(map == (void *) -1, "mmap")

    return map;
}

