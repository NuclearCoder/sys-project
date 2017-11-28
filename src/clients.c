//
// Created by nuclearcoder on 08/11/17.
//

#include "headers.h"

#include "clients.h"
#include "commands.h"
#include "misc.h"

static int errcl;

#define CLERR_THROW(cond, num)  if (cond) { errcl = num; return num; }
#define CLERR_THROW2(cond, num) if (cond) { errcl = num; return (void *) num; }

void perrorcl(void) {
    switch (errcl) {
    case CLERR_NONE:
        printf("No error.\n");
        break;
    case CLERR_TERMINATE:
        printf("Terminated by client.\n");
        break;
    case CLERR_READ_FAILED:
        printf("E] FIFO read failed: %s\n", strerror(errno));
        break;
    case CLERR_FIFO_CLOSED:
        printf("E] FIFO closed prematurely.\n");
        break;
    case CLERR_SHM_OPEN:
        printf("E] SHM open failed: %s\n", strerror(errno));
        break;
    case CLERR_SHM_UNLINK:
        printf("E] SHM unlink failed: %s\n", strerror(errno));
        break;
    case CLERR_SHM_MMAP:
        printf("E] SHM memory map failed: %s\n", strerror(errno));
        break;
    case CLERR_SEM_POST:
        printf("E] Semaphore post failed: %s\n", strerror(errno));
        break;
    case CLERR_THREAD_ARG:
        printf("E] Could not allocate thread arg: %s\n", strerror(errno));
        break;
    default:
        printf("E] Unknown error: %d\n", errcl);
    }
}

int handle_client(int fd) {
    pthread_t th;
    intptr_t ret;

    pthread_create(&th, NULL, client_thread, (void *) (intptr_t) fd);

    pthread_join(th, (void **) &ret);

    return (int) ret;
}

void *client_thread(void *arg) {
    int fd = (int) (intptr_t) arg;

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

    // call the command handler
    intptr_t ret = (intptr_t) handle_command(&map->sem, &map->p);

    // post the semaphor
    CLERR_THROW2(sem_post(&map->sem) == -1, CLERR_SEM_POST)

    errcl = ret;
    
    return (void *) ret;
}
