//
// Created by nuclearcoder on 2017-12-03.
//

#include "../common.h"

#include "../src/clients.h"

#include "shm.h"
#include "sem.h"
#include "fifo.h"

#include "client.h"

callback(default_callback)
{
    pDebug("Default callback");

    printf("Return code %d:\n%s\n------------\n", p->id, p->data);

    return (int) p->id;
}

static ccallback_t s_cb = default_callback;

void set_callback(ccallback_t cb)
{
    s_cb = cb;
}

void run_client(const char *fifoname, const char *command, ...)
{

    // pid will identify this process uniquely during its lifetime
    pid_t pid = getpid();

    // create shared memory segment and map it
    pmmap_t *map = create_and_map_shm(pid);

    // open semaphore
    init_sem(map);

    // open the named pipe
    int fd = open_fifo(fifoname);

    // write the packet data
    map->p.id = pid;

    // format
    va_list argptr;
    va_start(argptr, command);
    vsnprintf(map->p.data, PACKET_SIZE, command, argptr);
    va_end(argptr);

    pDebugV("Wrote: \"%s\"", map->p.data);

    write(fd, &map->p, sizeof(struct packet));

    // close the pipe
    close(fd);

    // wait for response
    wait_sem(map);

    pDebugV("Response: \"%s\"", map->p.data);

    int ret = s_cb(&map->p);

    (void) ret;

    pDebugV("Return value: %d", ret);


}
