//
// Created by nuclearcoder on 08/11/17.
//

#include "../common.h"

#include "clients.h"
#include "misc.h"

extern int errcl;

#define CLERR_THROW(cond, num)  if (cond) { errcl = num; return num; }
#define CLERR_THROW2(cond, num) if (cond) { errcl = num; *ret = num; return ret; }

int handle_client(int fd) {
    pthread_t th;
    int *arg, *ret;
    int retval;

    arg = malloc(sizeof(int));
    CLERR_THROW(arg == NULL, CLERR_OUT_OF_HEAP)
    
    *arg = fd;

    pthread_create(&th, NULL, client_thread, arg);
    pthread_join(th, (void **) &ret);

    retval = *ret;
    free(ret);

    return retval;
}

void *client_thread(void *arg) {
    int *ret = malloc(sizeof(int));
    CLERR_THROW2(ret == NULL, CLERR_OUT_OF_HEAP)

    int fd = *((int *) arg);
    free(arg);

    struct packet p;
    int r = exact_read(fd, &p, sizeof(struct packet));
    CLERR_THROW2(r == -1, CLERR_READ_FAILED)
    CLERR_THROW2(r == 1, CLERR_FIFO_CLOSED)

    printf(" * Client: %d\n", p.id);

    // create the SHM
    char name[32];
    snprintf(name, 32, "/sysp_shm_%d", p.id);

    int shmid = shm_open(name, O_RDWR, 0666);
    CLERR_THROW2(shmid == -1, CLERR_SHM_OPEN)

    // once we open the SHM on our end, unlink it for our exclusive use
    CLERR_THROW2(shm_unlink(name) == -1, CLERR_SHM_UNLINK)

    // map our variables
    pmmap_t *map = mmap(NULL, sizeof(pmmap_t),
                        PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
    CLERR_THROW2(map == (void *) -1, CLERR_SHM_MMAP)

    
    pDebugV("Received: \"%s\"", map->p.data);

    // call the command handler
    errcl = *ret = handle_command(map);

    // post the semaphore
    CLERR_THROW2(sem_post(&map->sem) == -1, CLERR_SEM_POST)
    
    return (void *) ret;
}
