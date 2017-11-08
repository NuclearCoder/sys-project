#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

int main() {
    int fd = open("cmdqueue", O_WRONLY | O_EXCL);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    uint32_t id = 0;
    uint32_t end = 0xF1F0BEEF;

    write(fd, &id, sizeof(id));
    write(fd, &end, sizeof(end));
    close(fd);

    return 0;
}