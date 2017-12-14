//
// Created by nuclearcoder on 2017-11-08.
//

#include "../common.h"

#include "misc.h"
#include "clients.h"
#include "commands.h"

int handle_command(pmmap_t *map) {
    int ret = CLERR_NONE;

    ifcmd(TERMINATE, map) {
        ret = callcmd(TERMINATE, map);
    } else ifcmd(INFO_USER, map) {
        ret = callcmd(INFO_USER, map);
    } else ifcmd(INFO_PROC, map) {
        ret = callcmd(INFO_PROC, map);
    } else {
        pset(&map->p, -1, "Unknown command: \"%s\"", strdup(map->p.data));
    }

    return ret;
}

int pset(struct packet *p, int id, const char *format, ...) {
    p->id = id;

    va_list argptr;
    va_start(argptr, format);
    int n = vsnprintf(p->data, PACKET_SIZE, format, argptr);
    va_end(argptr);

    return n;
}

int increpif(struct packet *p, sem_t *sem, bool cond) {
    if (!cond) return 0;

    p->id = 2;
    if (sem_wait(sem) == -1) {
        return -1;
    }

    p->data[0] = '\0';

    return 0;
}
