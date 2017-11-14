#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <semaphore.h>

#include "../src/clients.h"

int main() {

    pid_t pid = getpid();

    char name[32];
    snprintf(name, 32, "/sysp_shm_%d", pid);

    int shmid = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0666);
    if (shmid == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    if (ftruncate(shmid, sizeof(bool) + sizeof(struct packet)) == -1) {
        perror("ftruncate");
        return EXIT_FAILURE;
    }

    pmmap_t *map = mmap(NULL, sizeof(pmmap_t), PROT_READ | PROT_WRITE,
                        MAP_SHARED, shmid, 0);
    if (map == (void *) -1) {
        perror("mmap");
        return EXIT_FAILURE;
    }

    if (sem_init(&map->sem, 1, 0) == -1) {
        perror("sem_init");
        return EXIT_FAILURE;
    }

    int fd = open("cmdqueue", O_WRONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    map->p.id = pid;
    strncpy(map->p.data, "term", PACKET_SIZE);

    write(fd, &map->p, sizeof(struct packet));
    close(fd);

    if (sem_wait(&map->sem) == -1) {
        perror("sem_wait");
        return EXIT_FAILURE;
    }

    printf("Response: %s", map->p.data);

    sem_destroy(&map->sem);

    return 0;
}