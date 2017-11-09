#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../src/clients.h"

int main() {

    pid_t pid = getpid();

    char name[32];
    snprintf(name, 32, "shm_%d", pid);

    int shmid = shm_open(name, O_RDWR | O_CREAT, 0666);
    if (shmid == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    if (ftruncate(shmid, sizeof(struct packet)) == -1) {
        perror("ftruncate");
        return EXIT_FAILURE;
    }

    struct packet *p;

    if ((p = mmap(NULL, sizeof(struct packet),
                  PROT_NONE, MAP_SHARED,
                  shmid, 0)) == (void *) -1) {
        perror("mmap");
        return EXIT_FAILURE;
    }


    int fd = open("cmdqueue", O_WRONLY | O_EXCL);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    p->id = pid;
    strncat(p->data, "term", PACKET_SIZE);

    write(fd, p, sizeof(p));
    close(fd);



    return 0;
}