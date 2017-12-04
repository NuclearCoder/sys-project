//
// Created by nuclearcoder on 30/11/17
//

#include "../common.h"

#include "../src/clients.h"

static sem_t *sem = NULL;

void destroy_sem(void) {
    if (sem != NULL) {
        ERR(sem_destroy(sem) == -1, "destroy_sem")
    }
}

void init_sem(pmmap_t *map) {
    sem = &map->sem;
    ERR(sem_init(sem, 1, 0) == -1, "init_sem")
    atexit(destroy_sem); // schedule for destroy
}

void wait_sem(pmmap_t *map) {
    ERR(sem_wait(&map->sem) == -1, "wait_sem")
}

