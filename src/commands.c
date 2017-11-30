//
// Created by nuclearcoder on 28/11/17.
//

#include "headers.h"

#include "misc.h"
#include "clients.h"
#include "commands.h"

int handle_command(struct packet *p) {
    int ret = CLERR_NONE;

    ifcmd(TERMINATE, p) {
        ret = callcmd(TERMINATE, p);
    } else ifcmd(INFO_USER, p) {
        ret = callcmd(INFO_USER, p);
    } else ifcmd(INFO_PROC, p) {
        ret = callcmd(INFO_PROC, p);
    } else {
        pset(p, -1, "Unknown command: \"%s\"", strdup(p->data));
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
